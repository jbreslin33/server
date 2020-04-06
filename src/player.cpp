#include "player.h"

Player::Player(Client* client)
{

	mX = 0;
	mY = 0;

	//if 0 then ai	
	mClient = client; 
}
