#include "server.h"

#include "network.h"
#include "client.h"

Server::Server()
{
	this->mClientIdCounter = 0;
	this->mNetwork = new Network(this);


	this->startGameLoop();
}

void Server::startGameLoop()
{
	while(true)
	{
		this->mNetwork->readData();
	}
}

void Server::processData(std::string s)
{
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
