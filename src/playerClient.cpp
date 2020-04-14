#include <iostream>

#include "playerClient.h"

PlayerClient::PlayerClient(int id, int port, int personId) : Client(id,port,personId)
{
	mPlayer = nullptr;
}

