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


class Network
{
	private:

        int sock;
        struct sockaddr_in sa;
        char buffer[1024];
        ssize_t recsize;
        socklen_t fromlen;

	public:

	Network();

	void readData();

};

#endif
