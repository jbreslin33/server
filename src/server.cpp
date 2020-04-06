#include "server.h"
#include "utility.h"

Server::Server()
{
	mUtility = new Utility();
	mGameIdCounter = 0;
	mClientIdCounter = 0;

}

int Server::getNextGameId()
{
	mGameIdCounter++;
	return mGameIdCounter;
}

int Server::getNextClientId()
{
	mClientIdCounter++;
	return mClientIdCounter;
}

