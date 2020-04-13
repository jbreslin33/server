#include <iostream>
#include "player.h"
#include "vector3d.h"

#include "playerStates.h"
#include "playerStateMachine.h"

Player::Player(Client* client, int x, int y, int z) : MovePiece(x,y,z)
{
	mClient = client;



	//states
	GlobalPlayerState* mGlobalPlayerState = new GlobalPlayerState();
	
	mPlayerStateMachine = new PlayerStateMachine(this);    //setup the state machine

	mPlayerStateMachine->setCurrentState(mGlobalPlayerState);
    	mPlayerStateMachine->setPreviousState(nullptr);
    	mPlayerStateMachine->setGlobalState(mGlobalPlayerState);
    	//mPlayerStateMachine->changeState(nullptr);


}

void Player::update()
{
	printf("update in player\n");
	mPlayerStateMachine->update();
}
