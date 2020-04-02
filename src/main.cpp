#include <iostream>
#include <thread>

#include "relay.h"


void writeSocketData(Relay* relay)
{
	printf("in writeData");
	while (true)
	{
		if (relay->mMessage.length() > 0)
        	{

			int sock;
  			struct sockaddr_in sa;
  			int bytes_sent;
  			char buffer[200];
 
  			//strcpy(buffer, "hello to client from serve!");
  			strcpy(buffer, relay->mMessage.c_str());
 
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

	      		printf("sendto called"); 	
  			bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  			if (bytes_sent < 0) 
			{
    				printf("Error sending packet: %s\n", strerror(errno));
    				exit(EXIT_FAILURE);
  			}
 
  			close(sock); /* close the socket */
	  		relay->mMessage.clear();
		}
	}
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
		printf("waiting on port %d\n", 7654);

    		recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);

                if (recsize > 0) 
		{
                        buffer[recsize] = 0;
			if (buffer[0] == 49)
			{
				printf("MOVE\n");
			}
			if (buffer[0] == 50)
			{
				printf("NEW CLIENT\n");
				std::string port;
				for (int i = 1; i < 6; i++)
				{
					if (i == 1)
					{
						if (buffer[i] == 48)
						{
							//port is below 10000 and has leading zero from client so dont put in port string
						}
						else
						{
							port.push_back(buffer[i]);
						}
					}
					port.push_back(buffer[i]);
				}	
				relay->mPort = (unsigned short) strtoul(port.c_str(), NULL, 0);
				printf("PORT:%s\n",port.c_str());

				//lets send message back to client
				relay->mMessage = "hi client i got your message";

			}
			if (buffer[0] == 51)
			{
				printf("END GAME\n");
			}
                }
	}
}

int main(void)
{
	Relay relay;

        std::thread tReadSocketData (readSocketData, &relay);
        std::thread tWriteSocketData (writeSocketData, &relay);

        tReadSocketData.join();
        tWriteSocketData.join();

        return 0;

}
