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

void Client::sendMessage(std::string s)
{
        char cstr[s.size() + 1];
        strcpy(mBuffer, s.c_str());        // or pass &s[0]

        int socketId = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (socketId == -1)
        {
                printf("Error Creating Socket");
                exit(EXIT_FAILURE);
        }
        /*

        memset(&mNetwork->mClientVector.at(0)->mSocketAddressIn, 0, sizeof mNetwork->mClientVector.at(0)->mSocketAddressIn);

        mNetwork->mClientVector.at(0)->mSocketAddressIn.sin_family = AF_INET;

        mNetwork->mClientVector.at(0)->mSocketAddressIn.sin_addr.s_addr = inet_addr("127.0.0.1");

        mNetwork->mClientVector.at(0)->mSocketAddressIn.sin_port = htons(7654);
        */

        int bytes_sent = sendto(socketId, mBuffer, strlen(mBuffer), 0,(struct sockaddr*)&mSocketAddressIn, sizeof mSocketAddressIn);
        if (bytes_sent < 0)
        {
                printf("Error sending packet: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        close(socketId);
}

