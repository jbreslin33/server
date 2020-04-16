#include <iostream>
#include "player.h"

#include "playerStates.h"
#include "playerStateMachine.h"
#include "steering.h"
#include "common/2d/transformations.h"
#include <math.h>

//Player* homePlayerOne = new Player(this,homeClientOne,10,10,0);


Player::Player(Game* game, int x, int y, int z) : MovePiece(x,y,z)
{
	mClient = nullptr;
	mGame = game;
	
	//steering
	mSteering = new Steering(this);

	//states
	GlobalPlayerState* mGlobalPlayerState = new GlobalPlayerState();
	ChaseBallPlayerState* mChaseBallPlayerState = new ChaseBallPlayerState();
	
	mPlayerStateMachine = new PlayerStateMachine(this);    //setup the state machine

	mPlayerStateMachine->setCurrentState(nullptr);
    	mPlayerStateMachine->setPreviousState(nullptr);
    	mPlayerStateMachine->setGlobalState(mGlobalPlayerState);
    	mPlayerStateMachine->changeState(mChaseBallPlayerState);

}

void Player::update()
{



	//check if lost connection or switch to human
	checkIfHuman();	

  	//run the logic for the current state
	mPlayerStateMachine->update();

	//set looking at
	//mHeading = mSteering->mTarget - mPosition;
	mHeading = mPosition - mSteering->mTarget;
	mHeading.Normalize();

	mLooking = atan2(mHeading.x,mHeading.y) * 180 / 3.14;
	//atan2 (y,x) * 180 / PI;
	if (mClient)
	{
		printf("mLooking:%f",mLooking);
	}

	//RotateHeadingToFacePosition(mSteering->mTarget);
	
  	//calculate the combined steering force
	mSteering->calculate();

  	//if no steering force is produced decelerate the player by applying a
 	//braking force
	if (mSteering->mSteeringForce.isZero())
	{
		const double BrakingRate = 0.8;

		mVelocity = mVelocity * BrakingRate;
	}
  
  	//the steering force's side component is a force that rotates the 
  	//player about its axis. We must limit the rotation so that a player
  	//can only turn by PlayerMaxTurnRate rads per update.
	//double TurningForce = mSteering->sideComponent();
  
	//Clamp(TurningForce, -mMaxTurnRate, mMaxTurnRate);
  
  	//rotate the heading vector
	//Vec2DRotateAroundOrigin(mHeading, TurningForce);
	//printf("x:%f y:%f TurningForce:%f mHeading.x:%f mHeading.y:%f \n",mSteering->mSteeringForce.x,mSteering->mSteeringForce.y, TurningForce,mHeading.x,mHeading.y);

  
	//make sure the velocity vector points in the same direction as
  	//the heading vector
  	//mVelocity = mHeading * mVelocity.Length();

  
	//and recreate m_vSide
  	//mSide = mHeading.Perp();
  
  	//and recreate m_vSide
	//Vector2D accel = mHeading * mSteering->forwardComponent(); // m_dMass;
  
	//mVelocity += accel;
  
	//make sure player does not exceed maximum velocity
	mVelocity = mSteering->mSteeringForce;
  	mVelocity.Truncate(mMaxSpeed);

  	//update the position
  	mPosition += mVelocity;
}
/*
  //run the logic for the current state
  m_pStateMachine->Update();

  //calculate the combined steering force
  m_pSteering->Calculate();

  //if no steering force is produced decelerate the player by applying a
  //braking force
  if (m_pSteering->Force().isZero())
  {
    const double BrakingRate = 0.8;

    m_vVelocity = m_vVelocity * BrakingRate;
  }

  //the steering force's side component is a force that rotates the 
  //player about its axis. We must limit the rotation so that a player
  //can only turn by PlayerMaxTurnRate rads per update.
  double TurningForce =   m_pSteering->SideComponent();

  Clamp(TurningForce, -Prm.PlayerMaxTurnRate, Prm.PlayerMaxTurnRate);

  //rotate the heading vector
  Vec2DRotateAroundOrigin(m_vHeading, TurningForce);

  //make sure the velocity vector points in the same direction as
  //the heading vector
  m_vVelocity = m_vHeading * m_vVelocity.Length();
8
  //and recreate m_vSide
  m_vSide = m_vHeading.Perp();
8

  //now to calculate the acceleration due to the force exerted by
  //the forward component of the steering force in the direction
  //of the player's heading
  Vector2D accel = m_vHeading * m_pSteering->ForwardComponent() / m_dMass;

  m_vVelocity += accel;

  //make sure player does not exceed maximum velocity
  m_vVelocity.Truncate(m_dMaxSpeed);

  //update the position
  m_vPosition += m_vVelocity;


  //enforce a non-penetration constraint if desired
  if(Prm.bNonPenetrationConstraint)
  {
    EnforceNonPenetrationContraint(this, AutoList<PlayerBase>::GetAllMembers());
  }
  */


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
