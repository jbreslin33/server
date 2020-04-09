#ifndef PLAYER_H
#define PLAYER_H

class Client;

class Player
{
	public:
		Player(Client* client, int id, int startX, int startY);
		int mX;
		int mY;

		int mId;
		
		Client* mClient;

		void update();
	private:

};

#endif
