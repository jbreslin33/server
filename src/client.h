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


class Client
{
	public:
		Client(int id, struct sockaddr_in* socketAddressIn);

		void setId(int id);
		int getId();
	private:

		int mId;
		struct sockaddr_in* mSocketAddressIn;


};

#endif
