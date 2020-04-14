#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "client.h"

class Player;

class PlayerClient : public Client
{
	private:

	public:
		PlayerClient(int id, int port, int personId);
		Player* mPlayer;
};

#endif
