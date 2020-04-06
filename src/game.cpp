#include <iostream>

#include "game.h"

#include <sys/time.h>

Game::Game(int id)
{
	mId = id;
	printf("game id %d started.\n", mId);

	mRunning = true;

	mGameStartTime = getCurrentMilliseconds();
	mLastTime = mGameStartTime;
	mDelta = 0;
	mTickCount = 0;
}

long Game::getCurrentMilliseconds()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

void Game::update()
{
	mDelta = getCurrentMilliseconds() - mLastTime;

	if (mDelta > 30)
	{
		tick();	
		mLastTime = getCurrentMilliseconds();
	}
}

void Game::tick()
{
	//printf("tick:%ld\n",mDelta);
}

