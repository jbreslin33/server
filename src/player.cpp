#include <iostream>
#include "player.h"

#include "playerStateMachine.h"
#include "playerStates.h"
#include "playerControlStates.h"
#include "steering.h"
#include "client.h"
#include "common/2d/transformations.h"
#include <math.h>

//Player* homePlayerOne = new Player(this,homeClientOne,10,10,0);


Player::Player(Game* game, int x, int y, int z, double facingAngle) : MovePiece(x,y,z,facingAngle)
{
	mClient = nullptr;
	mGame = game;
	
	//steering
	mSteering = new Steering(this);
	
	//state machines
	mPlayerStateMachine = new PlayerStateMachine(this);    //setup the state machine
	mPlayerControlStateMachine = new PlayerStateMachine(this);    //setup the state machine

	//player states
	mGlobalPlayerState = new GlobalPlayerState();
	mInitPlayerState = new InitPlayerState();
	mWaitPlayerState = new WaitPlayerState();
	mHumanPlayerState = new HumanPlayerState();
	mChaseBallPlayerState = new ChaseBallPlayerState();
	
	//player control states
	mGlobalPlayerControlState = new GlobalPlayerControlState();
	mInitPlayerControlState = new InitPlayerControlState();
	mHumanPlayerControlState = new HumanPlayerControlState();
	mComputerPlayerControlState = new ComputerPlayerControlState();

	//set states
	//player states
	mPlayerStateMachine->setCurrentState(nullptr);
    	mPlayerStateMachine->setPreviousState(nullptr);
    	mPlayerStateMachine->setGlobalState(mGlobalPlayerState);
    	mPlayerStateMachine->changeState(mInitPlayerState);

	//player control states	
	mPlayerControlStateMachine->setCurrentState(nullptr);
    	mPlayerControlStateMachine->setPreviousState(nullptr);
    	mPlayerControlStateMachine->setGlobalState(mGlobalPlayerControlState);
    	mPlayerControlStateMachine->changeState(mInitPlayerControlState);

}

void Player::update()
{

	//check if lost connection or switch to human
	checkIfHuman();	
		
	mPlayerControlStateMachine->update();
	mPlayerStateMachine->update();

	//move
	if (mClient)
	{
        	mVelocity.x = mClient->mJoystickDirection.x;
        	mVelocity.y = mClient->mJoystickDirection.y;
		mRotateVelocity = mClient->mJoystickRotation;
	}

        //normalize
       	mVelocity.Normalize();
                
       	mVelocity.Truncate(mMaxSpeed);

        //add normalized velocity to current position   
        mPosition.x += mVelocity.x;
        mPosition.y += mVelocity.y;

       //rotate
       mFacingAngle += mRotateVelocity;

/*
	if (mClient)
	{
	//	int directionX =  mClient->mRight + (mClient->mLeft * -1);
         //       int directionY =  mClient->mDown + (mClient->mUp * -1);
          //      int rotate =  mClient->mRotateRight + (mClient->mRotateLeft * -1);

                mVelocity.x = directionX;
                mVelocity.y = directionY;
                mRotateVelocity = rotate;

                //normalize
                mVelocity.Normalize();
  		
		mVelocity.Truncate(mMaxSpeed);

                //add normalized velocity to current position   
                mPosition.x += mVelocity.x;
                mPosition.y += mVelocity.y;

                //rotate
                mFacingAngle += mRotateVelocity;
        }

	else
	{

  		//run the logic for the current state
		mPlayerStateMachine->update();

		//set looking at
	
		mHeading = mPosition - mSteering->mTarget;
		mHeading.Normalize();

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
	*/
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
