#include <iostream>

#include "game.h"
#include "client.h"
#include "player.h"
#include "server.h"
#include "utility.h"

#include <sys/time.h>

Game::Game(Server* server, int id)
{
	//server
	mServer = server;

	//message buffer...
	void* mBuffer;

	//class
	mId = id;
	
	printf("game id %d started.\n", mId);

	//is running
	mRunning = true;

	//ticks
	mGameStartTime = getCurrentMilliseconds();
	mLastTime = mGameStartTime;
	mDelta = 0;
	mTickCount = 0;

	//clients
	mClientIdCounter = 0;

	//make 4 players and clients
	Client* homeClientOne = new Client(getNextClientId(),0);
	mClientVector.push_back(homeClientOne);

	Client* homeClientTwo = new Client(getNextClientId(),0);
	mClientVector.push_back(homeClientTwo);

	Client* homeClientThree = new Client(getNextClientId(),0);
	mClientVector.push_back(homeClientThree);

	Client* awayClientOne = new Client(getNextClientId(),0);
	mClientVector.push_back(awayClientOne);

	Player* homePlayerOne = new Player(homeClientOne);
	mPlayerVector.push_back(homePlayerOne);
	Player* homePlayerTwo = new Player(homeClientTwo);
	mPlayerVector.push_back(homePlayerTwo);
	Player* homePlayerThree = new Player(homeClientThree);
	mPlayerVector.push_back(homePlayerThree);
	Player* awayPlayerOne = new Player(awayClientOne);
	mPlayerVector.push_back(awayPlayerOne);
	

}
void Game::processBuffer(char* buffer)
{
  	if (buffer[1] == 50)
	{
		printf("we have a 50 which is a connect.\n");
		std::string port;
        	for (int i = 2; i < 7; i++)
        	{
         		if (i == 1)
                        {
                        	if (buffer[i] == 48)
                                {
                                	//port is below 10000 and has leading zero from client so dont put in port string
                                }
                                else
                                {
                                	port.push_back(buffer[i]);
                                }
                       	}
                        else
                        {
                        	port.push_back(buffer[i]);
                        }
		}       
                //relay->mPort = stoi(port);
               	int portInt = stoi(port);

               	//lets find a client with a port 0 so its not being used by human
		for (int c = 0; c < mClientVector.size(); c++)
		{
			if (mClientVector.at(c)->mPort == 0)
			{
				printf("found client id: %d with port zero giving it port %d\n",mClientVector.at(c)->mId, portInt);
				mClientVector.at(c)->mPort = portInt;
		
               			//lets send message back to client and clients later....
              			std::string m = "2"; //new client
               	
				std::string id = std::to_string(mClientVector.at(c)->mId); 
               			m.append(mServer->mUtility->padZerosLeft(5,id)); //client id
               			mMessage = m;

				//break out
				c = mClientVector.size() + 3;

			}
		}
               	//Client* client = new Client(relay->mServer->getNextClientId(),portInt);
               	//relay->mServer->mClientVector.push_back(client);

               	//lets send message back to client and clients later....
		/*
              	std::string m = "2"; //new client

               	std::string id = std::to_string(client->mId); 
               	m.append(relay->mServer->mUtility->padZerosLeft(5,id)); //client id

               	relay->mMessage = m;
		*/
	}

}

int Game::getNextClientId()
{
        mClientIdCounter++;
        return mClientIdCounter;
}

int Game::getNextPlayerId()
{
        mPlayerIdCounter++;
        return mPlayerIdCounter;
}


long Game::getCurrentMilliseconds()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

void Game::update()
{
	mDelta = getCurrentMilliseconds() - mLastTime;

	if (mDelta > 30)
	{
		tick();	
		mLastTime = getCurrentMilliseconds();
	}
}

void Game::tick()
{
	//printf("tick:%ld\n",mDelta);
}

