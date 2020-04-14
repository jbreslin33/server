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
	//printf("x:%f y:%f\n",returnVelocity.x,returnVelocity.y);

	return (returnVelocity);
}

Vector2D Steering::calculate()
{
	mPlayer->mVelocity.Zero();

	mPlayer->mVelocity = sumForces();
}	

Vector2D Steering::sumForces()
{
	Vector2D force;

	force = seekTarget(mTarget);
	return force;
}


/*

Vector2D SteeringBehaviors::Seek(Vector2D target)
{

  Vector2D DesiredVelocity = Vec2DNormalize(target - m_pPlayer->Pos())
                            * m_pPlayer->MaxSpeed();

  return (DesiredVelocity - m_pPlayer->Velocity());
}
*/
