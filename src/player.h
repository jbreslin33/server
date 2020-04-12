#ifndef PLAYER_H
#define PLAYER_H

class Client;
class Vector3d;

class Player
{
	public:
		Player(Client* client, int id, int x, int y, int z);
		
		void update();

		Client* mClient;
		Vector3d* mPosition;
		Vector3d* mVelocity;

		int mId;
		double mSpeed;

	private:

};

#endif
