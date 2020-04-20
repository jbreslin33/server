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
		Vector2D mSideHeading;
		Vector2D mHeading; //is actually where we are pointing
		Vector2D mDesiredHeading; //where we want to point

		double mHeadingAngle; //to send to game clients
		double mRotateVelocity;
		double mVelocityAngle;


                double mMaxSpeed;
                double mMaxForce;
                double mMaxTurnRate;
		Utility utility;

};

#endif
