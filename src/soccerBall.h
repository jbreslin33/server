#ifndef BALL_H
#define BALL_H

class Client;
class Vector3d;

class Ball
{
	public:
		Ball(Client* client, int id, int x, int y, int z);
		
		void update();

		Client* mClient;
		Vector3d* mPosition;
		Vector3d* mVelocity;

		int mId;
		double mSpeed;

	private:

};

#endif
