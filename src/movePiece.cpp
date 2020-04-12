#include "movePiece.h"
#include "vector3d.h"


MovePiece::MovePiece(Client* client,int x, int y, int z) : BasePiece(x,y,z)
{
	mClient = client;
        mVelocity = new Vector3d(0,0,0);
}
