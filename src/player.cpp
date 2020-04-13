#include <iostream>
#include "player.h"

#include "playerStates.h"
#include "playerStateMachine.h"
#include "steering.h"

//Player* homePlayerOne = new Player(this,homeClientOne,10,10,0);


Player::Player(Game* game, Client* client, int x, int y, int z) : MovePiece(x,y,z)
{
	printf("c\n");
	mClient = client;
	mGame = game;

	//states
	GlobalPlayerState* mGlobalPlayerState = new GlobalPlayerState();
	ChaseBallPlayerState* mChaseBallPlayerState = new ChaseBallPlayerState();
	
	mPlayerStateMachine = new PlayerStateMachine(this);    //setup the state machine

	mPlayerStateMachine->setCurrentState(nullptr);
    	mPlayerStateMachine->setPreviousState(nullptr);
    	mPlayerStateMachine->setGlobalState(mGlobalPlayerState);
    	mPlayerStateMachine->changeState(mChaseBallPlayerState);
	printf("d\n");

	//steering
	//mSteering = new Steering(this);
}

void Player::update()
{
	mPlayerStateMachine->update();
}
