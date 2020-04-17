#ifndef PLAYER_H
#define PLAYER_

#include "movePiece.h"

class Client;
class PlayerStateMachine;
class Steering;
class Game;

class GlobalPlayerState;
class InitPlayerState;
class ChaseBallPlayerState;
class HumanPlayerState;

class GlobalPlayerControlState;
class InitPlayerControlState;
class ComputerPlayerControlState;
class HumanPlayerControlState;

class Player : public MovePiece
{
	public:
		Player(Game* game, int x, int y, int z, double facingAngle);
		
		void update();

		bool getHuman();
		void setHuman(bool b);
		void checkIfHuman();

		Client* mClient;
		Game* mGame;
		bool mHuman;

		//states machines
		PlayerStateMachine* mPlayerStateMachine;
		PlayerStateMachine* mPlayerControlStateMachine;

	       	//player states
       	 	GlobalPlayerState* mGlobalPlayerState;
        	InitPlayerState* mInitPlayerState;
        	ChaseBallPlayerState* mChaseBallPlayerState;

        	//player control states
        	GlobalPlayerControlState* mGlobalPlayerControlState;
        	InitPlayerControlState* mInitPlayerControlState;
        	HumanPlayerControlState* mHumanPlayerControlState;
        	ComputerPlayerControlState* mComputerPlayerControlState;

		//steering
		Steering* mSteering;


	private:

};

#endif
