#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "playerState.h"

class Player;

class PlayerState
{
	public: 
		PlayerState();
		virtual void enter(Player* player);
		virtual void execute(Player* player);
		virtual void exit(Player* player);

	private:


};

#endif
