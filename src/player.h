#ifndef PLAYER_H
#define PLAYER_

#include "movePiece.h"

class Client;
class PlayerStateMachine;
class Steering;

class Player : public MovePiece
{
	public:
		Player(Client* client, int x, int y, int z);
		
		void update();

		Client* mClient;

		//states
		PlayerStateMachine* mPlayerStateMachine;

		//steering
		Steering* mSteering;

	private:

};

#endif
