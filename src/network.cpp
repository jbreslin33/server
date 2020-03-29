#include "network.h"

#include "server.h"

Network::Network(Server* server)
{
	mServer = server;
	
	mListenSocket = new Socket(7654);

}

void Network::readData()
{
	mReceivedMessageSize = recvfrom(mSocket, (void*)mBuffer, sizeof mBuffer, 0, (struct sockaddr*)&mRemoteSocketAddressIn, &mFromLength);
        if (mReceivedMessageSize < 0) 
        {
        	fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
    
        printf("recsize: %d\n ", (int)mReceivedMessageSize);
        sleep(1);
       	printf("datagram: %.*s\n", (int)mReceivedMessageSize, mBuffer);

	mServer->processData(mBuffer, mRemoteSocketAddressIn);
}


