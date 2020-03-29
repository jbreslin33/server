#include "server.h"

#include "network.h"
#include "client.h"

Server::Server()
{
	this->mClientIdCounter = 0;

	this->mNetwork = new Network(this, 7654);

	this->startGameLoop();
}

void Server::startGameLoop()
{
	while(true)
	{
		this->mNetwork->readData();
	}
}

void Server::processData(std::string s, struct sockaddr_in socketAddressIn)
{
	/*
	struct in_addr {
               uint32_t       s_addr;    
           };
*/
	//printf("address: %d", socketAddressIn.in_addr.s_addr);
	printf("address: %d", socketAddressIn.sin_addr.s_addr);
	if (s.compare(0,1,"1") == 0)
	{
		//Move
		printf ("%s \n", "Move came in.");
		
	}
	if (s.compare(0,1,"2") == 0)
	{
		//new client
		printf ("%s \n", "New client connected.");

		this->mClientIdCounter++;
		Client* client = new Client(this->mClientIdCounter);
	}
}
