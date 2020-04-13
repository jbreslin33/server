#include "playerStates.h"
#include <iostream>

#include "player.h"
#include "steering.h"

/**** GlobalPlayerState ****************************/

GlobalPlayerState::GlobalPlayerState()
{
}

void GlobalPlayerState::enter(Player* player)
{
        printf("GlobalPlayerState::enter\n");
}
void GlobalPlayerState::execute(Player* player)
{
}
void GlobalPlayerState::exit(Player* player)
{
        printf("GlobalPlayerState::exit\n");
}

/**** InitPlayerState ****************************/

InitPlayerState::InitPlayerState()
{
}

void InitPlayerState::enter(Player* player)
{
        printf("InitPlayerState::enter\n");
}
void InitPlayerState::execute(Player* player)
{
}
void InitPlayerState::exit(Player* player)
{
        printf("InitPlayerState::exit\n");
}

/**** ChaseBallPlayerState ****************************/

ChaseBallPlayerState::ChaseBallPlayerState()
{
}

void ChaseBallPlayerState::enter(Player* player)
{
        printf("ChaseBallPlayerState::enter\n");
	player->mSteering->mSeekOn = true;
}
void ChaseBallPlayerState::execute(Player* player)
{
	player->mSteering->setTarget(player->mGame);
}
void ChaseBallPlayerState::exit(Player* player)
{
        printf("ChaseBallPlayerState::exit\n");
}


