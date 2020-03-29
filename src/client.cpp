#include "client.h"
#include <stdio.h>

Client::Client(int id)
{
	this->setId(id);
	printf ("New Client with id: %d \n", id);
}

void Client::setId(int id)
{
	this->mId = id;
}

int Client::getId()
{
	return this->mId;
}

