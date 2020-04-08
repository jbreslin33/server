#include <iostream>

#include "game.h"
#include "client.h"
#include "player.h"
#include "server.h"
#include "utility.h"

#include <sys/time.h>

//berkeley sockets
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

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

	Player* homePlayerOne = new Player(homeClientOne,getNextPlayerId());
	mPlayerVector.push_back(homePlayerOne);
	Player* homePlayerTwo = new Player(homeClientTwo,getNextPlayerId());
	mPlayerVector.push_back(homePlayerTwo);
	Player* homePlayerThree = new Player(homeClientThree,getNextPlayerId());
	mPlayerVector.push_back(homePlayerThree);
	Player* awayPlayerOne = new Player(awayClientOne,getNextPlayerId());
	mPlayerVector.push_back(awayPlayerOne);
	

}

void Game::processNewClient(std::vector<std::string> stringVector)
{
	int portInt = atoi(stringVector.at(3).c_str()); 

	bool foundClient = false;

       	//lets find a client with a port 0 so its not being used by human
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (!foundClient)
		{
			if (mClientVector.at(c)->mPort == 0)
			{
				printf("found client id: %d with port zero giving it port %d\n",mClientVector.at(c)->mId, portInt);
				mClientVector.at(c)->mPort = portInt;
	
				foundClient = true;
			}
		}
	}		

	if (!foundClient)
	{
		printf("Game is full!!! we need another game");
	}
}

void Game::processMove(std::vector<std::string> stringVector)
{
	int clientIdInt = atoi(stringVector.at(2).c_str()); 
	
	/*
	std::string clientId;
        for (int i = 2; i < 7; i++)
        {
               clientId.push_back(buffer[i]);
        }
        //relay->mPort = stoi(port);
        int clientIdInt = stoi(clientId);

	std::string up;
	//std::string right;
	//std::string down;
	//std::string left;
	*/
	

	//up.push_back(buffer[7]);	
	//printf("up:%s\n",up.c_str());
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (mClientVector.at(c)->mId == clientIdInt)
		{
			mClientVector.at(c)->mUp = atoi(stringVector.at(3).c_str()); 
			mClientVector.at(c)->mRight = atoi(stringVector.at(4).c_str()); 
			mClientVector.at(c)->mDown = atoi(stringVector.at(5).c_str()); 
			mClientVector.at(c)->mLeft = atoi(stringVector.at(6).c_str()); 


			/*
			if (buffer[7] == 49)
			{
				mClientVector.at(c)->mUp = 1;
			}
			if (buffer[7] == 48)
			{
				mClientVector.at(c)->mUp = 0;
			}
			
			if (buffer[8] == 49)
			{
				mClientVector.at(c)->mRight = 1;
			}
			if (buffer[8] == 48)
			{
				mClientVector.at(c)->mRight = 0;
			}

			if (buffer[9] == 49)
			{
				mClientVector.at(c)->mDown = 1;
			}
			if (buffer[9] == 48)
			{
				mClientVector.at(c)->mDown = 0;
			}
			
			if (buffer[10] == 49)
			{
				mClientVector.at(c)->mLeft = 1;
			}
			if (buffer[10] == 48)
			{
				mClientVector.at(c)->mLeft = 0;
			}
			*/
		}

	}
}

void Game::processBuffer(std::vector<std::string> stringVector)
{
	int code = atoi(stringVector.at(1).c_str()); 

	if (code == 1)
	{
		processMove(stringVector);
	}

	if (code == 2)
	{
		processNewClient(stringVector);
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

void Game::sendDataToNewClients()
{
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (mClientVector.at(c)->mPort != 0 && mClientVector.at(c)->mSentToClient == false)
		{
			//then we need to send to client so lets construct a messsage

                        std::string message = "2"; //new client

                        std::string id = std::to_string(mClientVector.at(c)->mId); //client id

                        message.append(mServer->mUtility->padZerosLeft(5,id)); //append client id
                        //printf("Game sending this message to client id %s: %s\n",id.c_str(),message.c_str()); //print to console what we are about to send

			sendToClient(mClientVector.at(c),message);

			mClientVector.at(c)->mSentToClient = true;
		}
	}
}

void Game::movePlayers()
{
	for (int p = 0; p < mPlayerVector.size(); p++)
	{
		mPlayerVector.at(p)->mX += ( mPlayerVector.at(p)->mClient->mRight + (mPlayerVector.at(p)->mClient->mLeft * -1) );
		mPlayerVector.at(p)->mY += ( mPlayerVector.at(p)->mClient->mDown  + (mPlayerVector.at(p)->mClient->mUp * -1) );	
	}
}

void Game::sendMovesToClients()
{
	for (int c = 0; c < mClientVector.size(); c++)
	{
		//only clients with ports
		if (mClientVector.at(c)->mPort != 0 && mClientVector.at(c)->mSentToClient == true)
		{
			//we could just send 5 a pop with no id??? that would be 20...
			std::string message = "1"; //move

			for (int p = 0; p < mPlayerVector.size(); p++)
			{

                        	std::string x = std::to_string(mPlayerVector.at(p)->mX); //player x
                        	std::string y = std::to_string(mPlayerVector.at(p)->mY); //player y 

				message.append(mServer->mUtility->padZerosLeft(5,x));
				message.append(mServer->mUtility->padZerosLeft(5,y));
			}

			if (c == 0)
			{	
                        	//printf("Game sending this message to clients: %s\n",message.c_str()); //print to console what we are about to send
			}

                        sendToClient(mClientVector.at(c),message);
		}
	}
}

void Game::tick()
{
	//printf("tick:%ld\n",mDelta);
	
	//any new clients then send them message with the port
	sendDataToNewClients();

	//move players
	movePlayers();

	//send moves to clients
	sendMovesToClients();

	
}

void Game::sendToClient(Client* client, std::string message)
{
	int sock;
        struct sockaddr_in sa;
        int bytes_sent;
       	char buffer[200];

       	strcpy(buffer, message.c_str());

       	/* create an Internet, datagram, socket using UDP */
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
       	if (sock == -1)
	{
       		/* if socket failed to initialize, exit */
               	printf("Error Creating Socket");
                exit(EXIT_FAILURE);
	}

        /* Zero out socket address */
        memset(&sa, 0, sizeof sa);

	/* The address is IPv4 */
       	sa.sin_family = AF_INET;

       	/* IPv4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value */
        sa.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654 */
        sa.sin_port = htons(client->mPort);

        bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
        if (bytes_sent < 0)
        {
        	printf("Error sending packet: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
       	}

	close(sock); /* close the socket */
}

