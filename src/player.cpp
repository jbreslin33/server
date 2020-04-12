#include "player.h"
#include "vector3d.h"

Player::Player(Client* client, int x, int y, int z) : MovePiece(x,y,z)
{
	mClient = client;
}
