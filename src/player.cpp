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
	else //ai
	{
                //calculate the combined steering force
                mSteering->calculate();

                //if no steering force is produced decelerate the player by applying a
                //braking force
		/*
                if (mSteering->mSteeringForce.isZero())
                {
                        const double BrakingRate = 0.8;

                        mVelocity = mVelocity * BrakingRate;
                }
		*/
  
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

	//this code will overide above code in regards to setting mHeadingAngle for transit to clients

	//what is desiredHeading? for now make it your velocity 
	//mDesiredHeading = mVelocity;	

	//what is current heading? its mHeading....dont need to set it here as it will be set later in code below...

	//int sign = mGame->mBall->mPosition.Sign(mDesiredHeading);	
	double angle = 0.0;
	if (mClient)
	{
		//result = acos (param) * 180.0 / PI;
		//angle = acos(v1•v2)
		mHeading.Normalize();
		angle = acos (mHeading.Dot(mVelocity));
		//printf("angle:%f\n",angle);
		//
		//double mVelocityAngle = atan2(0.5, 0.5)*180/3.14;
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

	
	//lets rotate to where we are going
	/*
	double radians = ( mDesiredFacingAngle * 3.14 ) / 180 ; 
	Vector2D V; 
	V.x = cos(radians);
	V.y = sin(radians);
	if (mClient)
	{
		printf("radians:%f x:%f y:%f \n",radians,V.x,V.y);
	}
	*/

	//desiredFacingAngle
	//mDesiredFacingAngle
	
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

void Player::detectBallCollision()
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

                	if (distance < mRadius / 2 + mGame->mPlayerVector.at(p)->mRadius / 2)
                	{
                        	playerCollision(mGame->mPlayerVector.at(p));
                	}
		}
        }
}

