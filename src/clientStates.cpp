#include "clientStates.h"
#include "clientStateMachine.h"
#include <iostream>

#include "client.h"
#include "steering.h"
#include "game.h"
#include "ball.h"
#include "player.h"
#include "common/2d/vector2d.h"

/**** GlobalClientState ****************************/

GlobalClientState::GlobalClientState()
{
}

void GlobalClientState::enter(Client* client)
{
        printf("GlobalClientState::enter\n");
}
void GlobalClientState::execute(Client* client)
{
	for (int p = 0; p < client->mGame->mPlayerVector.size(); p++)
	{
		if (client->mGame->mPlayerVector.at(p)->mClient == client)
		{
			//switch to human
                	if (client->mClientStateMachine->mCurrentState != client->mHumanClientState)
			{
                		client->mClientStateMachine->changeState(client->mHumanClientState);
			}
		}
	}
}
void GlobalClientState::exit(Client* client)
{
        printf("GlobalClientState::exit\n");
}

/**** InitClientState ****************************/

InitClientState::InitClientState()
{
}

void InitClientState::enter(Client* client)
{
        printf("InitClientState::enter\n");
}
void InitClientState::execute(Client* client)
{
	if (client->mClientStateMachine->mCurrentState != client->mWaitClientState)
	{
               	client->mClientStateMachine->changeState(client->mWaitClientState);
	}
}
void InitClientState::exit(Client* client)
{
        printf("InitClientState::exit\n");
}

/**** WaitClientState ****************************/

WaitClientState::WaitClientState()
{
}

void WaitClientState::enter(Client* client)
{
        printf("WaitClientState::enter\n");
}
void WaitClientState::execute(Client* client)
{
}
void WaitClientState::exit(Client* client)
{
        printf("WaitClientState::exit\n");
}

/**** HumanClientState ****************************/

HumanClientState::HumanClientState()
{
}

void HumanClientState::enter(Client* client)
{
        printf("HumanClientState::enter\n");
}
void HumanClientState::execute(Client* client)
{
	//check if human still
	bool human = false;
        for (int p = 0; p < client->mGame->mPlayerVector.size(); p++)
        {
                if (client->mGame->mPlayerVector.at(p)->mClient == client)
                {
			human = true;
                }
        }

	if (!human)
	{
		//switch to human
                if (client->mClientStateMachine->mCurrentState != client->mHumanClientState)
                {
                	client->mClientStateMachine->changeState(client->mHumanClientState);
		}

	}

	//get moves from remote client..in ai you can randomize these to get behaviors..
	client->mJoystickDirection.x =  client->mRight + (client->mLeft * -1);
        client->mJoystickDirection.y =  client->mDown + (client->mUp * -1);
        client->mJoystickRotation =  client->mRotateRight + (client->mRotateLeft * -1);

}

void HumanClientState::exit(Client* client)
{
        printf("HumanClientState::exit\n");
}



/**** ChaseBallClientState ****************************/

ChaseBallClientState::ChaseBallClientState()
{
}

void ChaseBallClientState::enter(Client* client)
{
        printf("ChaseBallClientState::enter\n");
	/*
	client->mSteering->mSeekOn = true;
	*/
}
void ChaseBallClientState::execute(Client* client)
{
	/*
	Vector2D v;
	v.x = client->mGame->mBall->mPosition.x;
	v.y = client->mGame->mBall->mPosition.y;

	client->mSteering->setTarget(v);
	*/
}
void ChaseBallClientState::exit(Client* client)
{
        printf("ChaseBallClientState::exit\n");
}


