#ifndef CLIENT_H
#define CLIENT_H

class Client
{
	private:

	public:
		Client(int id, int port);
		int mId;
		int mPort;

		bool mSentToClient;

		int mUp;
		int mRight;
		int mDown;
		int mLeft;
};

#endif
