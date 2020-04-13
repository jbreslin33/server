#include "basePiece.h"
#include "common/2d/vector2d.h"

int BasePiece::mNextId = 1;

BasePiece::BasePiece(int x, int y, int z)
{
        mPosition.x = x;
        mPosition.y = y;
	setId(mNextId);
}

void BasePiece::setId(int id)
{
	mId = id;
	mNextId++;	
}
