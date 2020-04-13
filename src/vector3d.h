#ifndef VECTOR3D_H 
#define VECTOR3D_H

class Vector3d
{

	public:
		Vector3d(double x, double y, double z);
		double mX;
		double mY;
		double mZ;
		
		double getLength();
		void normalize();

		double length();
		void truncate(double max);

	private:
};

#endif
