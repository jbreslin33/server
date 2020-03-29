#include "network.h"

#include "server.h"

Network::Network(Server* server)
{
	mServer = server;

        memset(&mSocketAddressIn, 0, sizeof mSocketAddressIn);
        mSocketAddressIn.sin_family = AF_INET;
        mSocketAddressIn.sin_addr.s_addr = htonl(INADDR_ANY);
        mSocketAddressIn.sin_port = htons(7654);
        mFromLength = sizeof mSocketAddressIn;

        mSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (bind(mSocket, (struct sockaddr *)&mSocketAddressIn, sizeof mSocketAddressIn) == -1) 
        {
                perror("error bind failed");
                close(mSocket);
                exit(EXIT_FAILURE);
        }
}

void Network::readData()
{
	mReceivedMessageSize = recvfrom(mSocket, (void*)mBuffer, sizeof mBuffer, 0, (struct sockaddr*)&mSocketAddressIn, &mFromLength);
        if (mReceivedMessageSize < 0) 
        {
        	fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
    
        printf("recsize: %d\n ", (int)mReceivedMessageSize);
        sleep(1);
       	printf("datagram: %.*s\n", (int)mReceivedMessageSize, mBuffer);

	mServer->processData(mBuffer);
}


