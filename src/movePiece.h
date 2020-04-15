#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "basePiece.h"
#include "common/2d/vector2d.h"

class MovePiece : public BasePiece
{
	public: 
		MovePiece(int x, int y, int z);

 		void update();

                Vector2D mVelocity;
		Vector2D mSide;
		Vector2D mHeading;

                double mMaxSpeed;
                double mMaxForce;
                double mMaxTurnRate;

};

#endif
