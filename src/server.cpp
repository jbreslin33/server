#include "relay.h"


Server::Server()
{
	this->mClientIdCounter = 0;

	this->mNetwork = new Network(this);

	this->startGameLoop();
}

void Server::startGameLoop()
{
	while(true)
	{
		this->mNetwork->mListenSocket->readData();
	}
}

void Server::processData(std::string s, struct sockaddr_in socketAddressIn)
{

	if (s.compare(0,1,"1") == 0)
	{
		//Move
		printf ("Move came in");
	}
	if (s.compare(0,1,"2") == 0)
	{

		//lets grab the port
		std::string port = s.substr(1,5);

		this->mClientIdCounter++;
		Client* client = new Client(this->mClientIdCounter, &socketAddressIn);
		mNetwork->mClientVector.push_back(client);
		
		printf ("Client: %d listening on port: %s\n", client->getId(), port.c_str());

		//make message to send to clients
		std::string message = "Server will send messages to port: ";
		message.append(port);
		client->sendMessageToClient(message);
	}
}
