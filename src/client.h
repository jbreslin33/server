#ifndef CLIENT_H
#define CLIENT_H

#include "common/2d/vector2d.h"

class Game;

class ClientStateMachine;

class GlobalClientState;
class InitClientState;
class WaitClientState;
class HumanClientState;
class ChaseBallClientState;

class Client
{
	public:
		Client(Game* game, int id, int port, int personId);

		void update();

		Game* mGame;

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

		//joystick
		Vector2D mJoystickDirection;
		double mJoystickRotation;

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
