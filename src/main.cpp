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

int main(void)
{
	Relay relay;

        std::thread tServer          (server, &relay);
        std::thread tReadSocketData (readSocketData, &relay);

        tServer.join();
        tReadSocketData.join();

        return 0;

}
