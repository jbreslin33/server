#ifndef SOCKET_H
#define SOCKET_H

class Network;

class Socket
{
	public:
		Socket(Network* network);

	private:
		Network* mNetwork;

		//Berkeley Sockets
        	int mSocketId;

        	struct sockaddr_in mSocketAddressIn;
        	struct sockaddr_in mRemoteSocketAddressIn;

        	char mBuffer[1024];
        	ssize_t mReceivedMessageSize;
        	socklen_t mFromLength;

        	int mPort;
};

#endif
