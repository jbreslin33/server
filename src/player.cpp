#include "player.h"

Player::Player(Client* client, int id)
{

	mX = 0;
	mY = 0;

	mId = id;

	//if 0 then ai	
	mClient = client; 
}
