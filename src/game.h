#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>
#include <iostream>
using namespace std::chrono;

class Client;
class Player;
class Server;

class Game
{
	private:

	public:
		Game(Server* server, int id);
		void update();
		void tick();
		void sendToClient(Client* client, std::string message);

		long getCurrentMilliseconds();

		//buffer
		void processBuffer(std::vector<std::string> stringVector);
		void processMove(std::vector<std::string> stringVector);
		void processNewClient(std::vector<std::string> stringVector);

		//send
		void sendDataToNewClients();
		void movePlayers();
		void sendMovesToClients();

		//message to clients
		std::string mMessage;

		//server
		Server* mServer;
	
		//class	
		int mId;

		//client
                int getNextClientId();
                std::vector<Client*> mClientVector;
                int mClientIdCounter;

		//player
                int getNextPlayerId();
                std::vector<Player*> mPlayerVector;
                int mPlayerIdCounter;

		//is running
		bool mRunning;

		//time
		long mGameStartTime;
		long mLastTime;
		long mDelta;
        	long mTickCount;

};

#endif
