#include "client.h"
#include <stdio.h>

Client::Client(int id, struct sockaddr_in* socketAddressIn)
{
	this->setId(id);
	printf ("New Client with id: %d \n", id);

	mSocketAddressIn = socketAddressIn;

        char *ip = inet_ntoa(socketAddressIn->sin_addr);
        printf("New Client with IP address: %s\n", ip);


}

void Client::setId(int id)
{
	this->mId = id;
}

int Client::getId()
{
	return this->mId;
}

