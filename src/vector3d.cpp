#include "vector3d.h"
#include <math.h>
#include <limits>

Vector3d::Vector3d(double x, double y, double z)
{
	mX = x;
	mY = y;
	mZ = z;
}

double Vector3d::getLength()
{
	return sqrt(mX * mX + mY * mY + mZ * mZ);
	double d = 0.0;
	return d;
}

void Vector3d::normalize()
{
	double vector_length = this->getLength();

  	if (vector_length > std::numeric_limits<double>::epsilon())
  	{
    		this->mX /= vector_length;
    		this->mY /= vector_length;
  	}
}


