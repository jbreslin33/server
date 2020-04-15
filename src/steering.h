#ifndef STEERING_H
#define STEERING_H

#include "common/2d/vector2d.h"

class Player;

class Steering
{
	public:
		Steering(Player* player);

		Vector2D mTarget;
		Vector2D mSteeringForce;

		bool mSeekOn;


		void setTarget(Vector2D target);
		Vector2D seekTarget(Vector2D target);
		Vector2D calculate();
		Vector2D sumForces();

		Player* mPlayer;
};

#endif
