#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "playerState.h"

class Player;

class PlayerState
{
	public: 
		PlayerState();
		void enter(Player* player);
		void execute(Player* player);
		void exit(Player* player);

	private:


};

#endif
