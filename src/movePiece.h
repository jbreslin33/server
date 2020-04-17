#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "basePiece.h"
#include "common/2d/vector2d.h"
#include "utility.h"

class MovePiece : public BasePiece
{
	public: 
		MovePiece(int x, int y, int z, double facingAngle);

 		void update();

		bool RotateHeadingToFacePosition(Vector2D target);


                Vector2D mVelocity;
		Vector2D mSide;
		Vector2D mHeading;

		double mFacingAngle;
		double mRotateVelocity;

                double mMaxSpeed;
                double mMaxForce;
                double mMaxTurnRate;
		Utility utility;

};

#endif
