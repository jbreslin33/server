#ifndef SERVER_H
#define SERVER_H

#include <vector>

class Game;
class Utility;

class Server
{
	private:

	public:
		Server();
		void update();
		int getNextGameId();

		Utility* mUtility;

		std::vector<Game*> mGameVector;

		int mGameIdCounter;
};
#endif
