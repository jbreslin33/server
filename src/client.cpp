#include "client.h"
#include <stdio.h>

Client::Client(int id, struct sockaddr_in* socketAddressIn)
{
	this->setId(id);

	//sockaddr_in remote client first made contact with us with
	mSocketAddressIn = socketAddressIn;

	//print ip to console
        char *ip = inet_ntoa(socketAddressIn->sin_addr);
        printf("New Client id: %d AND IP address: %s\n",id,ip);


}

void Client::setId(int id)
{
	this->mId = id;
}

int Client::getId()
{
	return this->mId;
}

