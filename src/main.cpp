#include <iostream>
#include <thread>

#include "relay.h"
#include "server.h"
#include "client.h"
#include "utility.h"

void server(Relay* relay)
{
	Server* theServer = new Server(); 
	relay->mServer = theServer;	

	while (true)
	{
				
	}
}


void writeSocketData(Relay* relay)
{
	while (true)
	{
		if (relay->mMessage.length() > 0)
        	{
			//we then should loop clients......
			for (int c = 0; c < relay->mServer->mClientVector.size(); c++)
			{

				int sock;
  				struct sockaddr_in sa;
  				int bytes_sent;
  				char buffer[200];
 
  				strcpy(buffer, relay->mMessage.c_str());
 
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
  				sa.sin_port = htons(relay->mServer->mClientVector.at(c)->mPort);

  				bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  				if (bytes_sent < 0) 
				{
    					printf("Error sending packet: %s\n", strerror(errno));
    					exit(EXIT_FAILURE);
  				}
 
  				close(sock); /* close the socket */
			}
	  		relay->mMessage.clear();
		}
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
			if (buffer[0] == 49)
			{
				printf("MOVE\n");

                                //lets send message back to client and clients later....
                                std::string m = "1"; //new client

                                //std::string id = std::to_string(client->mId);
                                //m.append(relay->mServer->mUtility->padZerosLeft(5,id)); //client id

				relay->mMessage = m;

			}
			if (buffer[0] == 50)
			{
				printf("NEW CLIENT\n");

				std::string port;
				for (int i = 1; i < 6; i++)
				{
					if (i == 1)
					{
						if (buffer[i] == 48)
						{
							//port is below 10000 and has leading zero from client so dont put in port string
						}
						else
						{
							port.push_back(buffer[i]);
						}
					}
					else
					{
						port.push_back(buffer[i]);
					}
				}	
				//relay->mPort = stoi(port);
				int portInt = stoi(port);

				//lets create a client
				Client* client = new Client(relay->mServer->getNextClientId(),portInt);
				relay->mServer->mClientVector.push_back(client);

				//lets send message back to client and clients later....
				std::string m = "2"; //new client

				std::string id = std::to_string(client->mId); 
				m.append(relay->mServer->mUtility->padZerosLeft(5,id)); //client id

				relay->mMessage = m;
			}
			if (buffer[0] == 51)
			{
				printf("END GAME\n");
                                
				//lets send message back to client and clients later....
                                std::string m = "3"; //new client

                                //std::string id = std::to_string(client->mId);
                                //m.append(relay->mServer->mUtility->padZerosLeft(5,id)); //client id

				relay->mMessage = m;
			}
                }
	}
}

int main(void)
{
	Relay relay;

        std::thread tReadSocketData (readSocketData, &relay);
        std::thread tWriteSocketData (writeSocketData, &relay);
        std::thread tServer          (server, &relay);

        tReadSocketData.join();
        tWriteSocketData.join();
        tServer.join();

        return 0;

}
