#ifndef SERVER_H
#define SERVER_H

#include <vector>

class Game;
class Client;
class Utility;

class Server
{
	private:

	public:
		Server();
		int getNextGameId();
		int getNextClientId();

		Utility* mUtility;

		std::vector<Game*> mGameVector;
		std::vector<Client*> mClientVector;

		int mGameIdCounter;
		int mClientIdCounter;
};
#endif
