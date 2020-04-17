#include <iostream>

#include "client.h"

Client::Client(int id, int port, int personId)
{
	mId = id;
	mPort = port;
	mPersonId = personId;

	mSentToClient = false;
	printf("client %d listening on port %d\n",id,port);

	mUp = 0;
	mRight = 0;
	mDown = 0;
	mLeft = 0;
	mRotateLeft = 0;
	mRotateRight = 0;
}

