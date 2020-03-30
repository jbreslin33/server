#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <string>

class Client
{
	public:
		Client(int id, struct sockaddr_in* socketAddressIn);

		void setId(int id);
		int getId();

		void sendMessage(std::string s);
		void sendMessageToClient(std::string s);
		
		int mId;
		struct sockaddr_in* mSocketAddressIn;
	private:

                //Berkeley Sockets
                int mSocketId;

                //struct sockaddr_in mSocketAddressIn;
                //struct sockaddr_in mRemoteSocketAddressIn;

                char mBuffer[1024];
                ssize_t mReceivedMessageSize;
                socklen_t mFromLength;

                int mPort;




};

#endif
