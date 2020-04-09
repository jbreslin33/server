#include "player.h"

Player::Player(Client* client, int id, int startX, int startY)
{

	mX = startX;
	mY = startY;

	mId = id;

	//if 0 then ai	
	mClient = client; 
}
