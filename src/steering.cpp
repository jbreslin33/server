#include "steering.h"
#include "common/2d/vector2d.h"
#include "player.h"

Steering::Steering(Player* player)
{

	mSeekOn = false;
	mPlayer = player; 
}

void Steering::setTarget(Vector2D target)
{
	mTarget = target;
}

Vector2D Steering::seekTarget(Vector2D target)
{
	Vector2D p; 
	p.x = mPlayer->mPosition.x;
	p.y = mPlayer->mPosition.y;

	Utility utility;

	Vector2D DesiredVelocity = utility.Vec2DNormalize(target - p)
                            * mPlayer->mMaxSpeed;

	Vector2D v; 
	v.x = mPlayer->mVelocity.x;
	v.y = mPlayer->mVelocity.y;

	Vector2D returnVelocity = DesiredVelocity - v;

	return (returnVelocity);
}

Vector2D Steering::calculate()
{
	mSteeringForce.Zero();

	mSteeringForce = sumForces();

	mSteeringForce.Truncate(mPlayer->mMaxForce);

	return mSteeringForce;
}	

Vector2D Steering::sumForces()
{
	Vector2D force;

	if (mSeekOn)
	{
		force += seekTarget(mTarget);
	}

	return force;
}

//--------------------------- SideComponent ------------------------------
//
//  //  calculates the side component of the steering force
//------------------------------------------------------------------------
double Steering::sideComponent()
{
  return mPlayer->mSide.Dot(mSteeringForce) * mPlayer->mMaxTurnRate;
}
//------------------------- ForwardComponent -----------------------------
//
//  calculates the forward component of the steering force
//------------------------------------------------------------------------
double Steering::forwardComponent()
{
  return mPlayer->mHeading.Dot(mSteeringForce);
}



