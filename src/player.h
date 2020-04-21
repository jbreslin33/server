#ifndef PLAYER_H
#define PLAYER_H

#include "movePiece.h"

class Client;
class PlayerStateMachine;
class Steering;
class Game;
class Ball;

class GlobalPlayerState;
class InitPlayerState;
class WaitPlayerState;
class HumanPlayerState;
class ChaseBallPlayerState;

class GlobalPlayerControlState;
class InitPlayerControlState;
class ComputerPlayerControlState;
class HumanPlayerControlState;

class Player : public MovePiece
{
	public:
		Player(Game* game, int x, int y, int z, double facingAngle, double diameter);
		
		void update();

		bool getHuman();
		void setHuman(bool b);
		void checkIfHuman();

                //collision
                void detectPlayerCollision();
                void playerCollision(Player* player);
                void ballCollision(Ball* ball);

		Client* mClient;
		Game* mGame;
		bool mHuman;

		//states machines
		PlayerStateMachine* mPlayerStateMachine;
		PlayerStateMachine* mPlayerControlStateMachine;

	       	//player states
       	 	GlobalPlayerState* mGlobalPlayerState;
        	InitPlayerState* mInitPlayerState;
        	WaitPlayerState* mWaitPlayerState;
        	HumanPlayerState* mHumanPlayerState;
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
