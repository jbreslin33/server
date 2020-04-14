#ifndef PLAYER_H
#define PLAYER_

#include "movePiece.h"

class Client;
class PlayerStateMachine;
class Steering;
class Game;

class Player : public MovePiece
{
	public:
		Player(Game* game, Client* client, int x, int y, int z);
		
		void update();

		bool getHuman();
		void setHuman(bool b);
		void checkIfHuman();

		Client* mClient;
		Game* mGame;
		bool mHuman;

		//states
		PlayerStateMachine* mPlayerStateMachine;

		//steering
		Steering* mSteering;


	private:

};

#endif
