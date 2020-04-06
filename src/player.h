#ifndef PLAYER_H
#define PLAYER_H

class Client;

class Player
{
	public:
		Player();
		int mX;
		int mY;
		Client* mClient;

		void update();
	private:

};

#endif
