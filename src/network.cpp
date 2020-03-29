#include "network.h"

#include "server.h"
#include "socket.h"

Network::Network(Server* server)
{
	mServer = server;
	
	mListenSocket = new Socket(this,7654);

}



