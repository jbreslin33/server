#ifndef BALL_H
#define BAL_H

#include "movePiece.h"

class Game;
class Player;

class Ball : public MovePiece
{
	public:
		Ball(Game* game, int x, int y, int z, double facingAngle, double diameter);
		
		void update();

		void detectPlayerCollision();
		void playerCollision(Player* player);
		Player* mPlayer;
		Player* mLastPlayer;

		Game* mGame;
		int mPlayerTimeoutCounter;


	private:

};

#endif
