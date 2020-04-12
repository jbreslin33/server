#ifndef PLAYERSTATEMACHINE_H
#define PLAYERSTATEMACHINE_H

class PlayerState;
class Player;

class PlayerStateMachine
{

	public:
		PlayerStateMachine(Player* mOwner);

		Player* mOwner;

		PlayerState* mGlobalState;
		PlayerState* mCurrentState;
		PlayerState* mPreviousState;

		void setCurrentState(PlayerState* playerState);
		void setPreviousState(PlayerState* playerState);
		void setGlobalState(PlayerState* playerState);
		PlayerState* getCurrentState();

		void update();

		void changeState(PlayerState* playerState);


};

#endif

