#ifndef PLAYERSTATES_H
#define PLAYERSTATES_H

#include "playerState.h"

class Player;

class GlobalPlayerState : public PlayerState
{

	public:
		GlobalPlayerState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};

class InitPlayerState : public PlayerState
{

	public:
		InitPlayerState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};

class HumanPlayerState : public PlayerState
{

	public:
		HumanPlayerState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};



class ChaseBallPlayerState : public PlayerState
{

	public:
		ChaseBallPlayerState();

 		void enter(Player* player);
 		void execute(Player* player);
 		void exit(Player* player);
};





#endif
