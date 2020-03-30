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
/*
                 int mSocketId;

                //struct sockaddr_in mSocketAddressIn;
                //struct sockaddr_in mRemoteSocketAddressIn;

                char mBuffer[1024];
                ssize_t mReceivedMessageSize;
                socklen_t mFromLength;

                int mPort;
*/

void Client::sendMessageToClient(std::string s)
{
        struct sockaddr_in sa;
        char buffer[1024];
	int sock;
	int bytes_sent;

        char cstr[s.size() + 1];
        strcpy(buffer, s.c_str());        // or pass &s[0]

        sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (sock == -1)
        {
                printf("Error Creating Socket");
                exit(EXIT_FAILURE);
        }

        memset(&sa, 0, sizeof sa);

        sa.sin_family = AF_INET;

        sa.sin_addr.s_addr = inet_addr("127.0.0.1");

        sa.sin_port = htons(8765);

        bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
        if (bytes_sent < 0)
        {
                printf("Error sending packet: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        close(sock);
}

