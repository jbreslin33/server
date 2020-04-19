#ifndef CLIENT_H
#define CLIENT_H

class ClientStateMachine;

class GlobalClientState;
class InitClientState;
class WaitClientState;
class HumanClientState;
class ChaseBallClientState;

class Client
{
	public:
		Client(int id, int port, int personId);

		void update();

		int mId;
		int mPort;
		int mPersonId;

		bool mSentToClient;

		int mUp;
		int mRight;
		int mDown;
		int mLeft;
		int mRotateLeft;
		int mRotateRight;

		//states

		//states machines
                ClientStateMachine* mClientStateMachine;

                //player states
                GlobalClientState* mGlobalClientState;
                InitClientState* mInitClientState;
                WaitClientState* mWaitClientState;
                HumanClientState* mHumanClientState;
                ChaseBallClientState* mChaseBallClientState;


	private:
};

#endif
