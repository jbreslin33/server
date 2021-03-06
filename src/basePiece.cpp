#include "basePiece.h"
#include "common/2d/vector2d.h"

int BasePiece::mNextId = 1;

BasePiece::BasePiece(int x, int y, int z, double diameter)
{
	//start position
        mStartPosition.x = x;
        mStartPosition.y = y;

	//use this for movement
        mPosition.x = x;
        mPosition.y = y;

	setId(mNextId);

	mDiameter = diameter;
}

void BasePiece::setId(int id)
{
	mId = id;
	mNextId++;	
}
