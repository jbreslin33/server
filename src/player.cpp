#include "player.h"
#include "vector3d.h"

Player::Player(Client* client, int id, int x, int y, int z)
{

	mPosition = new Vector3d(x,y,z);	
	mVelocity = new Vector3d(0,0,0);	

	mId = id;

	mSpeed = 0.25;

	//if 0 then ai	
	mClient = client; 
}
