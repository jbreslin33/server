#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "basePiece.h"

class MovePiece : public BasePiece
{
	public: 
		MovePiece(int x, int y, int z);

 		void update();

                Vector3d* mVelocity;

                double mSpeed;

};

#endif
