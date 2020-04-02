#include "server.h"
#include "utility.h"

Server::Server()
{
	mUtility = new Utility();
	mClientIdCounter = 0;
}

int Server::getNextClientId()
{
	mClientIdCounter++;
	return mClientIdCounter;
}
