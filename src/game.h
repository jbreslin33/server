#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>
#include <iostream>
using namespace std::chrono;

class Client;
class PlayerClient;
class Player;
class Server;
class Ball;

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
		void requestPlayerClientAndPlayer(std::vector<std::string> stringVector);

		//send
		void sendDataToNewClients();
		void movePlayers();
		void moveBall();
		void sendMovesToClients();

		int mPitchWidth;
		int mPitchHeight;

		//message to clients
		std::string mMessage;

		//server
		Server* mServer;

		//ball
		Ball* mBall;
	
		//class	
		int mId;

		//client
                int getNextClientId();
                std::vector<Client*> mClientVector;
                std::vector<PlayerClient*> mPlayerClientVector;
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
