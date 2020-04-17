#ifndef PLAYERCONTROLSTATES_H
#define PLAYERCONTROLSTATES_H

#include "playerState.h"

class Player;

class GlobalPlayerControlState : public PlayerState
{

	public:
		GlobalPlayerControlState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};

class InitPlayerControlState : public PlayerState
{

	public:
		InitPlayerControlState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};

class HumanPlayerControlState : public PlayerState
{

	public:
		HumanPlayerControlState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};



class ComputerPlayerControlState : public PlayerState
{

	public:
		ComputerPlayerControlState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};

#endif
