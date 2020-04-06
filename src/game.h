#ifndef GAME_H
#define GAME_H

class Game
{
	private:

	public:
		Game(int id);
		void update();
		void tick();
		int mId;
		bool mRunning;
};

#endif
