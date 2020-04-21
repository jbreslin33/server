#include <iostream>
#include "player.h"

#include "playerStateMachine.h"
#include "playerStates.h"
#include "playerControlStates.h"
#include "steering.h"
#include "client.h"
#include "game.h"
#include "ball.h"
#include "common/2d/transformations.h"
#include <math.h>

//Player* homePlayerOne = new Player(this,homeClientOne,10,10,0);


Player::Player(Game* game, int x, int y, int z, double facingAngle, double diameter) : MovePiece(x,y,z,facingAngle,diameter)
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
	else //ai
	{
                //calculate the combined steering force
                mSteering->calculate();

                //make sure player does not exceed maximum velocity
                mVelocity = mSteering->mSteeringForce;
	}

        //normalize
       	mVelocity.Normalize();
                
       	mVelocity.Truncate(mMaxSpeed);

        //add normalized velocity to current position   
        mPosition.x += mVelocity.x;
        mPosition.y += mVelocity.y;
      
       	//set mHeadingAngle to send to clients based on rotateVelocity from client joysticks etc.
       	mHeadingAngle += mRotateVelocity;

	mHeadingAngle = fmod(mHeadingAngle,360.0);

	double angle = 0.0;
	if (mClient)
	{
		mHeading.Normalize();
		angle = acos (mHeading.Dot(mVelocity));
		double mVelocityAngle = atan2(mVelocity.x, mVelocity.y)*180/3.14;

		if (mVelocity.isZero())
		{

		}
		else
		{
			if (mVelocityAngle > 179 && mVelocityAngle < 181)
			{
				mHeadingAngle = 0;	
			}

			if (mVelocityAngle > 134 && mVelocityAngle < 136)
			{
				mHeadingAngle = 45;	
			}

			if (mVelocityAngle > 89 && mVelocityAngle < 91)
			{
				mHeadingAngle = 90;	
			}

			if (mVelocityAngle > 44 && mVelocityAngle < 46)
			{
				mHeadingAngle = 135;	
			}

			if (mVelocityAngle > -1 && mVelocityAngle < 1 )
			{
				mHeadingAngle = 180;	
			}

			if (mVelocityAngle > -46 && mVelocityAngle < -44)
			{
				mHeadingAngle = 225;	
			}

			if (mVelocityAngle > -91 && mVelocityAngle < -89)
			{
				mHeadingAngle = 270;	
			}

			if (mVelocityAngle > -136 && mVelocityAngle < -134)
			{
				mHeadingAngle = 315;	
			}
		}
		//printf("mHeadingAngle:%f mVelocityAngle:%f\n",mHeadingAngle,mVelocityAngle);
	}
	detectPlayerCollision();	
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

void Player::playerCollision(Player* player)
{
        printf("player:%d collided with player:%d\n",mId,player->mId);
}

void Player::ballCollision(Ball* ball)
{

}

void Player::detectPlayerCollision()
{
        for (int p = 0; p < mGame->mPlayerVector.size(); p++)
        {
		if (mGame->mPlayerVector.at(p) != this)
		{
                	double dx = mPosition.x - mGame->mPlayerVector.at(p)->mPosition.x;
                	double dy = mPosition.y - mGame->mPlayerVector.at(p)->mPosition.y;
                	double distance = sqrt(dx * dx + dy * dy);

                	if (distance < mDiameter / 2 + mGame->mPlayerVector.at(p)->mDiameter / 2)
                	{
                        	playerCollision(mGame->mPlayerVector.at(p));
                	}
		}
        }
}

