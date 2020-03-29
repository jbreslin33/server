#include "server.h"

#include "network.h"

Server::Server()
{
	this->mNetwork = new Network();

	while(true)
	{
		this->mNetwork->readData();
	}

}
