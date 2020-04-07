#include <iostream>
#include <thread>

#include "relay.h"
#include "server.h"
#include "client.h"
#include "utility.h"
#include "game.h"
#include "rondo.h"

void server(Relay* relay)
{
	Server* theServer = new Server(); 
	relay->mServer = theServer;	

	//create game here. later this could be scheduled like a game or practice..
	
	Game* rondo = new Rondo(theServer, theServer->getNextGameId());
	relay->mServer->mGameVector.push_back(rondo);

	while (true)
	{
		relay->mServer->update();
	}	
}

void readSocketData(Relay* relay)
{
	int sock;
  	struct sockaddr_in sa; 
  	char buffer[1024];
  	ssize_t recsize;
  	socklen_t fromlen;

  	memset(&sa, 0, sizeof sa);
  	sa.sin_family = AF_INET;
  	sa.sin_addr.s_addr = htonl(INADDR_ANY);
  	sa.sin_port = htons(7654);
  	fromlen = sizeof sa;

  	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  	if (bind(sock, (struct sockaddr *)&sa, sizeof sa) == -1)
       	{
    		perror("error bind failed");
    		close(sock);
    		exit(EXIT_FAILURE);
  	}

  	for (;;) 
	{
		printf("waiting on port %d\n", 7654);

    		recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);

                if (recsize > 0) 
		{
                        buffer[recsize] = 0;
			char* cBuffer;
			cBuffer = (char*)buffer;
				
			int n = int(buffer[0]);
			int e = n - 49;	
			printf("game element:%d\n",e);
			relay->mServer->mGameVector.at(e)->processBuffer(cBuffer);				
                }
	}
}

void writeSocketData(Relay* relay)
{
	while (true)
	{
		for (int g = 0; g < relay->mServer->mGameVector.size(); g++)
		{
			if (relay->mServer->mGameVector.at(g)->mMessage.length() > 0)
			{
				for (int c = 0; c < relay->mServer->mGameVector.at(g)->mClientVector.size(); c++)
				{
					int sock;
  					struct sockaddr_in sa;
  					int bytes_sent;
  					char buffer[200];
 
  					strcpy(buffer, relay->mServer->mGameVector.at(g)->mMessage.c_str());
 
  					/* create an Internet, datagram, socket using UDP */
  					sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  					if (sock == -1) 
					{
      						/* if socket failed to initialize, exit */
      						printf("Error Creating Socket");
     	 					exit(EXIT_FAILURE);
  					}
 
  					/* Zero out socket address */
  					memset(&sa, 0, sizeof sa);
  
 	 				/* The address is IPv4 */
 	 				sa.sin_family = AF_INET;
 
  	 				/* IPv4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value */
  					sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  					/* sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654 */
  					sa.sin_port = htons(relay->mServer->mGameVector.at(g)->mClientVector.at(c)->mPort);

  					bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  					if (bytes_sent < 0) 
					{
    						printf("Error sending packet: %s\n", strerror(errno));
    						exit(EXIT_FAILURE);
  					}
 
  					close(sock); /* close the socket */
				}
			}
	  		relay->mServer->mGameVector.at(g)->mMessage.clear();
		}
	}
}


int main(void)
{
	Relay relay;

        std::thread tServer          (server, &relay);
        std::thread tReadSocketData (readSocketData, &relay);
        std::thread tWriteSocketData (writeSocketData, &relay);

        tServer.join();
        tReadSocketData.join();
        tWriteSocketData.join();

        return 0;

}
