#include <iostream>

#include "game.h"
#include <chrono>

using namespace std::chrono;

Game::Game(int id)
{
	mId = id;
	printf("game id %d started.\n", mId);
/*
	milliseconds ms = duration_cast< milliseconds >
	(
    		system_clock::now().time_since_epoch()
	);
	*/

	mRunning = true;
}

void Game::update()
{

	//printf("update game id: %d \n", mId);
	/*

	double ns = 1000000000.0 / 60.0;
    	double delta = 0;

   	long lastTime = System.nanoTime();
    	long timer = System.currentTimeMillis();

    	while (mRunning) 
	{
        	long now = System.nanoTime();
        	delta += (now - lastTime) / ns;
        	lastTime = now;

        	while (delta >= 1) 
		{
            		tick();
            		delta--;
        	}
    	}
	*/
}

void Game::tick()
{

}

