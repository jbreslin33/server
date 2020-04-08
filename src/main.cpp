//berkeley socket for read server
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> /* for close() for socket */ 
#include <stdlib.h>

#include <iostream>
#include <thread>

#include "server.h"
#include "client.h"
#include "utility.h"
#include "game.h"
#include "rondo.h"

void serverThread(Server* server)
{
	while (server->mRunning == true)
	{
		server->update();
	}	
}

void readSocketData(Server* server)
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
		//printf("waiting on port %d\n", 7654);

    		recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);

                if (recsize > 0) 
		{
                        buffer[recsize] = 0;
			char* cBuffer;
			cBuffer = (char*)buffer;
				
			int n = int(buffer[0]);
			int e = n - 49;	
			//printf("game element:%d\n",e);
			server->mGameVector.at(e)->processBuffer(cBuffer);				
                }
	}
}

int main(void)
{
	Server server;
	
	Game* rondo = new Rondo(&server, server.getNextGameId());
	server.mGameVector.push_back(rondo);

        std::thread tServer          (serverThread, &server);
        std::thread tReadSocketData (readSocketData, &server);

        tServer.join();
        tReadSocketData.join();

        return 0;

}
