#ifndef SERVER_H
#define SERVER_H

#include <vector>

class Client;
class Utility;

class Server
{
	private:

	public:
		Server();
		int getNextClientId();

		Utility* mUtility;
		std::vector<Client*> mClientVector;
		int mClientIdCounter;
};
#endif
