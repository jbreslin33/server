#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <iostream>
#include <fstream>



class Game;
class Utility;

class Server
{
	private:

	public:
		Server();
		void update();
		int getNextGameId();
	       	void log(std::string s);

		Utility* mUtility;

		std::vector<Game*> mGameVector;

		int mGameIdCounter;
		bool mRunning;
};
#endif
