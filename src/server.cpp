#include "server.h"

#include "network.h"

Server::Server()
{
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
