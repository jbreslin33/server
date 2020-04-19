#include <iostream>

#include "game.h"
#include "client.h"
#include "player.h"
#include "ball.h"
#include "server.h"
#include "utility.h"

#include <sys/time.h>
//berkeley sockets #include <stdlib.h> #include <stdio.h> #include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <math.h> 
#include "common/2d/vector2d.h"

#include "playerStateMachine.h"
#include "playerStates.h"



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

	//players and ball
	Player* homePlayerOne = new Player(this,10,10,0,0.0);
	mPlayerVector.push_back(homePlayerOne);

	Player* homePlayerTwo = new Player(this,10,-10,0,90.0);
	mPlayerVector.push_back(homePlayerTwo);

	Player* homePlayerThree = new Player(this,-10,-10,0,180.0);
	mPlayerVector.push_back(homePlayerThree);

	Player* awayPlayerOne = new Player(this,-10,10,0,270.0);
	mPlayerVector.push_back(awayPlayerOne);
	
	mBall = new Ball(this,0,0,0,90.0);

	awayPlayerOne->mPlayerStateMachine->changeState(awayPlayerOne->mChaseBallPlayerState);


}

void Game::startGame(std::vector<std::string> stringVector)
{
        for (int p = 0; p < mPlayerVector.size(); p++)
        {
                mPlayerVector.at(p)->mPosition.x = mPlayerVector.at(p)->mStartPosition.x;
                mPlayerVector.at(p)->mPosition.y = mPlayerVector.at(p)->mStartPosition.y;
        }

}

void Game::requestClient(std::vector<std::string> stringVector)
{
	int personIdInt = atoi(stringVector.at(2).c_str()); 
	int portInt = atoi(stringVector.at(3).c_str()); 

	// if this person requesting already has a client instance on server than rock on and just update the port if needed	
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (mClientVector.at(c)->mPersonId == personIdInt)
		{
			if (mClientVector.at(c)->mPort == portInt)
			{
				//printf("Person ID:%d already has a client and port is good to go at:%d.\n",personIdInt, portInt);
			}
			else
			{
				mClientVector.at(c)->mPort = portInt;
				mClientVector.at(c)->mSentToClient = false;
				printf("Person ID:%d already has a client. Updating port to: %d\n and sending confirmation to client again.",personIdInt, portInt);

			}
			return;
		}
	}

	//fall thru make a new client instance
	Client* client = new Client(getNextClientId(),0,0);
	mClientVector.push_back(client);
	client->mPersonId = personIdInt;
	printf("Make new Client for Person ID:%d \n",personIdInt);
}

void Game::requestPlayer(std::vector<std::string> stringVector)
{
	int personIdInt = atoi(stringVector.at(2).c_str()); 
	int portInt = atoi(stringVector.at(3).c_str()); 

	//who is this client
	for (int c = 0; c < mClientVector.size(); c++)
	{
		if (mClientVector.at(c)->mPersonId == personIdInt)
		{
			//found client	lets see if we can give a player a pointer to this client		
			
			for (int p = 0; p < mPlayerVector.size(); p++)
			{
				//but first make sure client is not assigned to another player already
				if (mClientVector.at(c) == mPlayerVector.at(p)->mClient)
				{
					return; //becuase this client is already assigned to a player...
				}
	
				//we go this far so client is not linked to player try to find a player with nullptr client...

				if (mPlayerVector.at(p)->mClient == nullptr)
				{
					//we got a player with a nullptr client
					mPlayerVector.at(p)->mClient = mClientVector.at(c);	
					printf("Able to assign a player with id:%d to person id:%d with port:%d\n",mPlayerVector.at(p)->mId,personIdInt,portInt);
					return;
				}
			}
		}
	}

	printf("not able to assign a player to person:%d with port:%d\n",personIdInt,portInt);

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
			mClientVector.at(c)->mRotateLeft = atoi(stringVector.at(7).c_str()); 
			mClientVector.at(c)->mRotateRight = atoi(stringVector.at(8).c_str()); 
		}
	}
}

void Game::processBuffer(std::vector<std::string> stringVector)
{

	if (stringVector.at(1).compare(0,1,"m") == 0)
	{
		processMove(stringVector);
	}

	if (stringVector.at(1).compare(0,1,"j") == 0)
	{
		requestClient(stringVector);
	}

	if (stringVector.at(1).compare(0,1,"p") == 0)
	{
		requestPlayer(stringVector);
	}
	
	if (stringVector.at(1).compare(0,1,"g") == 0)
	{
		startGame(stringVector);
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

			message.append("j"); //new client code	
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

void Game::moveBall()
{
	mBall->mVelocity.x = 0;	
	mBall->mVelocity.y = 0;	


	mBall->mVelocity.Normalize();

	mBall->mPosition.x += mBall->mVelocity.x;
	mBall->mPosition.y += mBall->mVelocity.y;
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
			message.append("m"); //move code
			message.append(",");


			for (int p = 0; p < mPlayerVector.size(); p++)
			{

                        	std::string id = std::to_string(mPlayerVector.at(p)->mId); //player id 
                        	std::string x  = std::to_string(mPlayerVector.at(p)->mPosition.x); //player x
                        	std::string y  = std::to_string(mPlayerVector.at(p)->mPosition.y); //player y 
                        	std::string facingAngle = std::to_string(mPlayerVector.at(p)->mFacingAngle); //left foot angle 

				message.append(id);
				message.append(",");
				message.append(x);
				message.append(",");
				message.append(y);
				message.append(",");
				message.append(facingAngle);
				message.append(",");
			}

			//add ball
                        std::string x  = std::to_string(mBall->mPosition.x); //ball x
                        std::string y  = std::to_string(mBall->mPosition.y); //ball y 
			message.append(x);
			message.append(",");
			message.append(y);
			message.append(",");

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
	
	//call update on clients
        for (int p = 0; p < mClientVector.size(); p++)
        {
                mClientVector.at(p)->update();
        }
	
	
	//call update on players
	for (int p = 0; p < mPlayerVector.size(); p++)
	{
		mPlayerVector.at(p)->update();
	}


	//send moves to clients
	sendMovesToClients();
	
	//any new clients then send them message with the port
	sendDataToNewClients();

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

