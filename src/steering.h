#ifndef STEERING_H
#define STEERING_H

struct Vector2D;
class Player;

class Steering
{
	public:
		Steering(Player* player);

		Vector2D* mTarget;
		bool mSeekOn;

		void setTarget(Vector2D* target);
		Vector2D seekTarget(Vector2D target);

		Player* mPlayer;
};

#endif
