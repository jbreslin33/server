#include <iostream>

#include "client.h"

Client::Client(int id, int port)
{
	mId = id;
	mPort = port;
	mSentToClient = false;
	printf("client %d listening on port %d\n",id,port);
}

