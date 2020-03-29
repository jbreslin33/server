#include "server.h"

#include "network.h"

Server::Server()
{
	this->mNetwork = new Network(this);

	while(true)
	{
		this->mNetwork->readData();
	}

}
