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

	//pitch size
	mPitchWidth = 105;
	mPitchHeight = 68;

	//lets setup our own cartesian coordinate system on server...than let clients translate it
	
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
	Client* homeClientOne = new Client(getNextClientId(),0,0);
	mClientVector.push_back(homeClientOne);

	Client* homeClientTwo = new Client(getNextClientId(),0,0);
	mClientVector.push_back(homeClientTwo);

	Client* homeClientThree = new Client(getNextClientId(),0,0);
	mClientVector.push_back(homeClientThree);

	Client* awayClientOne = new Client(getNextClientId(),0,0);
	mClientVector.push_back(awayClientOne);


	Player* homePlayerOne = new Player(homeClientOne,getNextPlayerId(),30,30);
	mPlayerVector.push_back(homePlayerOne);
	Player* homePlayerTwo = new Player(homeClientTwo,getNextPlayerId(),30,-30);
	mPlayerVector.push_back(homePlayerTwo);
	Player* homePlayerThree = new Player(homeClientThree,getNextPlayerId(),-30,-30);
	mPlayerVector.push_back(homePlayerThree);

	Player* awayPlayerOne = new Player(awayClientOne,getNextPlayerId(),0,0);
	mPlayerVector.push_back(awayPlayerOne);

	//assign players to clients
	homeClientOne->mPlayer = homePlayerOne;
	homeClientTwo->mPlayer = homePlayerTwo;
	homeClientThree->mPlayer = homePlayerThree;
	
	awayClientOne->mPlayer = awayPlayerOne;

}

void Game::processNewClient(std::vector<std::string> stringVector)
{
	int personIdInt = atoi(stringVector.at(2).c_str()); 
	int portInt = atoi(stringVector.at(3).c_str()); 

	bool foundClient = false;

       	//lets find a client with a port 0 so its not being used by human

	bool foundPersonId = false;	
	
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (mClientVector.at(c)->mPersonId == personIdInt)
		{
			foundPersonId = true;
			printf("Person ID:%d already has a client.\n",personIdInt);
			return;
		}
	}

	//continue on if person does not have a client yet
	if (foundPersonId == false)
	{
		for (int c = 0; c < mClientVector.size(); c++)
		{
			if (!foundClient)
			{
				if (mClientVector.at(c)->mPort == 0)
				{
					printf("found client id: %d with port zero giving it port %d\n",mClientVector.at(c)->mId, portInt);
					mClientVector.at(c)->mPort = portInt;
					mClientVector.at(c)->mPersonId = personIdInt;
	
					foundClient = true;
				}
			}
		}
	}		

	if (!foundClient)
	{
		printf("Game is full.\n");
	}
}

void Game::processMove(std::vector<std::string> stringVector)
{
	int clientIdInt = atoi(stringVector.at(2).c_str()); 
	
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (mClientVector.at(c)->mId == clientIdInt)
		{
			mClientVector.at(c)->mUp = atoi(stringVector.at(3).c_str()); 
			mClientVector.at(c)->mRight = atoi(stringVector.at(4).c_str()); 
			mClientVector.at(c)->mDown = atoi(stringVector.at(5).c_str()); 
			mClientVector.at(c)->mLeft = atoi(stringVector.at(6).c_str()); 
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
			std::string message = "";
		
			message.append(std::to_string(mId)); //gameID
			message.append(",");	

			message.append("2"); //new client code	
			message.append(",");	

                        message.append(std::to_string(mClientVector.at(c)->mId)); //client id
			message.append(",");	 //extra comma

                        //message.append(mServer->mUtility->padZerosLeft(5,id)); //append client id
			printf("TO NEW CLIENT:%s\n",message.c_str());
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
			std::string message = "";
			message.append(std::to_string(mId)); //game id
			message.append(",");
			message.append("1"); //move code
			message.append(",");


			for (int p = 0; p < mPlayerVector.size(); p++)
			{

                        	std::string id = std::to_string(mPlayerVector.at(p)->mId); //player id 
                        	std::string x  = std::to_string(mPlayerVector.at(p)->mX); //player x
                        	std::string y  = std::to_string(mPlayerVector.at(p)->mY); //player y 

				message.append(id);
				message.append(",");
				message.append(x);
				message.append(",");
				message.append(y);
				message.append(",");
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

