#include <iostream>
#include "player.h"

#include "playerStates.h"
#include "playerStateMachine.h"
#include "steering.h"
#include "common/2d/transformations.h"
#include <math.h>

//Player* homePlayerOne = new Player(this,homeClientOne,10,10,0);


Player::Player(Game* game, int x, int y, int z, double facingAngle) : MovePiece(x,y,z,facingAngle)
{
	mClient = nullptr;
	mGame = game;
	
	//steering
	mSteering = new Steering(this);

	//states
	GlobalPlayerState* mGlobalPlayerState = new GlobalPlayerState();
	InitPlayerState* mInitPlayerState = new InitPlayerState();
	ChaseBallPlayerState* mChaseBallPlayerState = new ChaseBallPlayerState();
	
	mPlayerStateMachine = new PlayerStateMachine(this);    //setup the state machine

	mPlayerStateMachine->setCurrentState(nullptr);
    	mPlayerStateMachine->setPreviousState(nullptr);
    	mPlayerStateMachine->setGlobalState(mGlobalPlayerState);
    	mPlayerStateMachine->changeState(mInitPlayerState);

}

void Player::update()
{

	//check if lost connection or switch to human
	checkIfHuman();	

  	//run the logic for the current state
	mPlayerStateMachine->update();

	//set looking at
	
	mHeading = mPosition - mSteering->mTarget;
	mHeading.Normalize();

	//mFacingAngle = atan2(mHeading.x,mHeading.y) * 180 / 3.14;
	
	if (mClient)
	{
		//printf("mFacingAngle:%f\n",mFacingAngle);
	}

  	//calculate the combined steering force
	mSteering->calculate();

  	//if no steering force is produced decelerate the player by applying a
 	//braking force
	if (mSteering->mSteeringForce.isZero())
	{
		const double BrakingRate = 0.8;

		mVelocity = mVelocity * BrakingRate;
	}
  
	//make sure player does not exceed maximum velocity
	mVelocity = mSteering->mSteeringForce;
  	mVelocity.Truncate(mMaxSpeed);

  	//update the position
  	mPosition += mVelocity;
}

void Player::checkIfHuman()
{
}

bool Player::getHuman()
{
	return mHuman;
}

void Player::setHuman(bool b)
{
	mHuman = b;
}
