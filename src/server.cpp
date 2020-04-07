#include "server.h"
#include "utility.h"
#include "game.h"

Server::Server()
{
	mUtility = new Utility();
	mGameIdCounter = 0;

	mRunning = true;
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


void Server::log(std::string s)
{
        std::ofstream ofs;
        ofs.open ("server.log", std::ofstream::out | std::ofstream::app);
        ofs << s << std::endl;
        ofs.close();
}

