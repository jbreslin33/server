#ifndef STEERING_H
#define STEERING_H

class Vector3d;

class Steering
{
	public:
		Steering();

		Vector3d* mTarget;
		bool mSeekOn;

		void setTarget(Vector3d* target);
};

#endif
