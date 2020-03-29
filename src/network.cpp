#include "network.h"

Network::Network(Server* server)
{

	mServer = server;

        memset(&sa, 0, sizeof sa);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = htonl(INADDR_ANY);
        sa.sin_port = htons(7654);
        fromlen = sizeof sa;

        sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (bind(sock, (struct sockaddr *)&sa, sizeof sa) == -1) 
        {
                perror("error bind failed");
                close(sock);
                exit(EXIT_FAILURE);
        }
/*
        for (;;) 
        {
                recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);
                if (recsize < 0) 
                {
                        fprintf(stderr, "%s\n", strerror(errno));
                        exit(EXIT_FAILURE);
                }
    
                printf("recsize: %d\n ", (int)recsize);
                sleep(1);
                printf("datagram: %.*s\n", (int)recsize, buffer);
        }
*/
}


void Network::readData()
{
	recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);
        if (recsize < 0) 
        {
        	fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
    
        printf("recsize: %d\n ", (int)recsize);
        sleep(1);
       	printf("datagram: %.*s\n", (int)recsize, buffer);
}

