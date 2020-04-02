#include <iostream>

#include "client.h"

Client::Client(int id, int port)
{
	mId = id;
	mPort = port;
	printf("client %d listening on port %d\n",id,port);
}

