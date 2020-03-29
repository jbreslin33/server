#ifndef SERVER_H
#define SERVER_H

#include <string>

class Network;

class Server
{
	private:
		Network* mNetwork;

	public:	

		Server();
		void startGameLoop();
		void processData(std::string s);
		
		int mClientIdCounter;
};


#endif
