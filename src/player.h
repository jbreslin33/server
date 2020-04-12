#ifndef PLAYER_H
#define PLAYER_

#include "movePiece.h"

class Client;


class Player : public MovePiece
{
	public:
		Player(Client* client, int x, int y, int z);
		
		void update();

	private:

};

#endif
