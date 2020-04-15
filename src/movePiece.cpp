#include "movePiece.h"
#include "common/2d/vector2d.h"

MovePiece::MovePiece(int x, int y, int z) : BasePiece(x,y,z)
{
        mVelocity.x = x;
        mVelocity.y = y;
	mMaxSpeed = 0.25;
	mMaxForce = 1.0;
}
