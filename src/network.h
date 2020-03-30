#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <vector>

class Server;
class Socket;
class Client;

class Network
{
	public:

	Network(Server* server);

	Server* mServer;
	Socket* mListenSocket;

	std::vector<Client*> mClientVector;



	private:

        int mSocket;

        struct sockaddr_in mSocketAddressIn;
        struct sockaddr_in mRemoteSocketAddressIn;

        char mBuffer[1024];
        ssize_t mReceivedMessageSize;
        socklen_t mFromLength;

	int mListenPort;


};

#endif
