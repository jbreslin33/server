#ifndef SERVER_H
#define SERVER_H

#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

class Network;

class Server
{
	private:
		Network* mNetwork;

	public:	

		Server();
		void startGameLoop();
		void processData(std::string s, struct sockaddr_in mSocketAddressIn);
		
		int mClientIdCounter;
	     
		struct sockaddr_in mSocketAddressIn;

};


#endif
