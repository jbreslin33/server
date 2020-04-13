#include "steering.h"

Steering::Steering()
{

	mTarget = nullptr;
	mSeekOn = false;
}

void Steering::setTarget(Vector3d* target)
{
	mTarget = target;
}



