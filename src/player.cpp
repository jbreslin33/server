#include <iostream>
#include "player.h"
#include "vector3d.h"

#include "playerStates.h"
#include "playerStateMachine.h"
#include "steering.h"

Player::Player(Client* client, int x, int y, int z) : MovePiece(x,y,z)
{
	mClient = client;

	//states
	GlobalPlayerState* mGlobalPlayerState = new GlobalPlayerState();
	ChaseBallPlayerState* mChaseBallPlayerState = new ChaseBallPlayerState();
	
	mPlayerStateMachine = new PlayerStateMachine(this);    //setup the state machine

	mPlayerStateMachine->setCurrentState(nullptr);
    	mPlayerStateMachine->setPreviousState(nullptr);
    	mPlayerStateMachine->setGlobalState(mGlobalPlayerState);
    	mPlayerStateMachine->changeState(mChaseBallPlayerState);

	//steering
	mSteering = new Steering();
}

void Player::update()
{
	mPlayerStateMachine->update();
}
