#ifndef PLAYER_H
#define PLAYER_H

class Client;

class Player
{
	public:
		Player(Client* client);
		int mX;
		int mY;
		Client* mClient;

		void update();
	private:

};

#endif
