#include "playerStateMachine.h"
#include "playerState.h"

PlayerStateMachine::PlayerStateMachine(Player* owner)
{
	mOwner = mOwner;

	mGlobalState = nullptr;
	mCurrentState = nullptr;
	mPreviousState = nullptr;
}

void PlayerStateMachine::update()
{

	if (mGlobalState)
	{
		mGlobalState->execute(mOwner);
	}	

	if (mCurrentState)
	{
		mCurrentState->execute(mOwner);
	}	

}

PlayerState* PlayerStateMachine::getCurrentState()
{
	return mCurrentState;
}

void PlayerStateMachine::setCurrentState(PlayerState* playerState)
{
	mCurrentState = playerState;
}

void PlayerStateMachine::setGlobalState(PlayerState* playerState)
{
	mGlobalState = playerState;
}

void PlayerStateMachine::changeState(PlayerState* newState)
{
	mPreviousState = mCurrentState;

        if(mCurrentState)
        {
        	mCurrentState->exit(mOwner);
        }

        mCurrentState = newState;

        if(mCurrentState)
        {
        	mCurrentState->enter(mOwner);
	}
}

