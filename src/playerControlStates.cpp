#include "playerStateMachine.h"
#include "playerControlStates.h"
#include <iostream>

#include "player.h"
#include "steering.h"
#include "game.h"
#include "ball.h"
#include "common/2d/vector2d.h"

/**** GlobalPlayerControlState ****************************/

GlobalPlayerControlState::GlobalPlayerControlState()
{
}

void GlobalPlayerControlState::enter(Player* player)
{
        printf("GlobalPlayerControlState::enter\n");
}
void GlobalPlayerControlState::execute(Player* player)
{
}
void GlobalPlayerControlState::exit(Player* player)
{
        printf("GlobalPlayerControlState::exit\n");
}

/**** InitPlayerControlState ****************************/

InitPlayerControlState::InitPlayerControlState()
{
}

void InitPlayerControlState::enter(Player* player)
{
        printf("InitPlayerControlState::enter\n");
}
void InitPlayerControlState::execute(Player* player)
{
	if (player->mClient)
	{
 		player->mPlayerControlStateMachine->changeState(player->mHumanPlayerControlState);
	}
	else
	{
 		player->mPlayerControlStateMachine->changeState(player->mComputerPlayerControlState);
	}
}
void InitPlayerControlState::exit(Player* player)
{
        printf("InitPlayerControlState::exit\n");
}

/**** HumanPlayerControlState ****************************/

HumanPlayerControlState::HumanPlayerControlState()
{
}

void HumanPlayerControlState::enter(Player* player)
{
        printf("HumanPlayerControlState::enter\n");
}
void HumanPlayerControlState::execute(Player* player)
{
	if (player->mClient == nullptr)
	{
 		player->mPlayerControlStateMachine->changeState(player->mComputerPlayerControlState);
	}

}
void HumanPlayerControlState::exit(Player* player)
{
        printf("HumanPlayerControlState::exit\n");
}



/**** ComputerPlayerControlState ****************************/

ComputerPlayerControlState::ComputerPlayerControlState()
{
}

void ComputerPlayerControlState::enter(Player* player)
{
        printf("ComputerPlayerControlState::enter\n");
}
void ComputerPlayerControlState::execute(Player* player)
{
	if (player->mClient)
	{
 		player->mPlayerControlStateMachine->changeState(player->mHumanPlayerControlState);
	}

}
void ComputerPlayerControlState::exit(Player* player)
{
        printf("ComputerPlayerControlState::exit\n");
}


