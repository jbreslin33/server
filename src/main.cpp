#include <iostream>
#include <thread>

#include "relay.h"


void writeData(Relay* relay)
{
	int sock;
  	struct sockaddr_in sa;
  	int bytes_sent;
  	char buffer[200];
 
  	strcpy(buffer, "hello to client from serve!");
 
  	/* create an Internet, datagram, socket using UDP */
  	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  	if (sock == -1) 
	{
      		/* if socket failed to initialize, exit */
      		printf("Error Creating Socket");
      		exit(EXIT_FAILURE);
  	}
 
  	/* Zero out socket address */
  	memset(&sa, 0, sizeof sa);
  
  	/* The address is IPv4 */
  	sa.sin_family = AF_INET;
 
   	/* IPv4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value */
  	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  	/* sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654 */
  	sa.sin_port = htons(8765);
 
  	bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  	if (bytes_sent < 0) 
	{
    		printf("Error sending packet: %s\n", strerror(errno));
    		exit(EXIT_FAILURE);
  	}
 
  	close(sock); /* close the socket */
}

void readSocketData(Relay* relay)
{
	int sock;
  	struct sockaddr_in sa; 
  	char buffer[1024];
  	ssize_t recsize;
  	socklen_t fromlen;

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

	/*
        while (true)
        {
                //relay->mListenSocket->readData();
                //relay->readData();
                relay->log("read Data");
        }
	*/
}

int main(void)
{
	Relay relay;

        std::thread socketReader (readSocketData, &relay);
        std::thread writer       (writeData, &relay);

        socketReader.join();
        writer.join();

        return 0;

}
