#ifndef CLIENT_H
#define CLIENT_H

class Player;

class Client
{
	private:

	public:
		Client(int id, int port, int personId);
		int mId;
		int mPort;
		int mPersonId;

		bool mSentToClient;

		int mUp;
		int mRight;
		int mDown;
		int mLeft;

		Player* mPlayer;
};

#endif
