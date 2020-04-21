#include "ball.h"
#include "game.h"
#include "player.h"

Ball::Ball(Game* game, int x, int y, int z, double facingAngle, double diameter) : MovePiece(x,y,z,facingAngle, diameter)
{
	mGame = game;
	mPlayerTimeoutCounter = 0;
	mPlayer = nullptr;
	mLastPlayer = nullptr;
	//needs state machine...
}

void Ball::update()
{
	detectPlayerCollision();

	if (mPlayer)
	{
		mPosition = mPlayer->mPosition;	
	}
}

void Ball::playerCollision(Player* player)
{
	mLastPlayer = mPlayer;
	mPlayer = player;
}
void Ball::detectPlayerCollision()
{
	for (int p = 0; p < mGame->mPlayerVector.size(); p++)
	{
        	if (mPlayer != mGame->mPlayerVector.at(p))
        	{
                	double dx = mPosition.x - mGame->mPlayerVector.at(p)->mPosition.x;
                	double dy = mPosition.y - mGame->mPlayerVector.at(p)->mPosition.y;
                	double distance = sqrt(dx * dx + dy * dy);

                	if (distance < mDiameter / 2 + mGame->mPlayerVector.at(p)->mDiameter / 2)
                	{
                       		playerCollision(mGame->mPlayerVector.at(p));
                	}
		}
        }
}

