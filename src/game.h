#ifndef GAME_H
#define GAME_H

#include <chrono>
using namespace std::chrono;


class Game
{
	private:

	public:
		Game(int id);
		void update();
		void tick();
		long getCurrentMilliseconds();

		int mId;
		bool mRunning;

		//time
		long mGameStartTime;
		long mLastTime;
		long mDelta;
        	long mTickCount;

};

#endif
