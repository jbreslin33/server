#ifndef SERVER_H
#define SERVER_H

#include <vector>

class Client;

class Server
{
	private:

	public:
		Server();
		std::vector<Client*> mClientVector;

		int mClientIdCounter;

		int getNextClientId();
};
#endif
