#include "basePiece.h"
#include "vector3d.h"

int BasePiece::mNextId = 1;

BasePiece::BasePiece(int x, int y, int z)
{
        mPosition = new Vector3d(x,y,z);
	setId(mNextId);
}

void BasePiece::setId(int id)
{
	mId = id;
	mNextId++;	
}
