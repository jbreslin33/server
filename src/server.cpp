#include "server.h"

Server::Server()
{
	mClientIdCounter = 0;
}

int Server::getNextClientId()
{
	mClientIdCounter++;
	return mClientIdCounter;
}
