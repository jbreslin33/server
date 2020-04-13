#include "movePiece.h"
#include "vector3d.h"

MovePiece::MovePiece(int x, int y, int z) : BasePiece(x,y,z)
{
        mVelocity = new Vector3d(0,0,0);
	mMaxSpeed = 0.25;
}
