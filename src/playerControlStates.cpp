#include "playerStates.h"
#include <iostream>

#include "player.h"
#include "steering.h"
#include "game.h"
#include "ball.h"
#include "common/2d/vector2d.h"

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

/**** HumanPlayerState ****************************/

HumanPlayerState::HumanPlayerState()
{
}

void HumanPlayerState::enter(Player* player)
{
        printf("HumanPlayerState::enter\n");
}
void HumanPlayerState::execute(Player* player)
{
}
void HumanPlayerState::exit(Player* player)
{
        printf("HumanPlayerState::exit\n");
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
	Vector2D v;
	v.x = player->mGame->mBall->mPosition.x;
	v.y = player->mGame->mBall->mPosition.y;

	player->mSteering->setTarget(v);
}
void ChaseBallPlayerState::exit(Player* player)
{
        printf("ChaseBallPlayerState::exit\n");
}


