#include "server.h"
#include "utility.h"
#include "game.h"

Server::Server()
{
	mUtility = new Utility();
	mGameIdCounter = 0;
}

int Server::getNextGameId()
{
	mGameIdCounter++;
	return mGameIdCounter;
}

void Server::update()
{
	for (int i = 0; i < mGameVector.size(); i++)
	{
		mGameVector.at(i)->update();		
	}                 

}

