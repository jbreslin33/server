#ifndef BALL_H
#define BAL_H

#include "movePiece.h"

class Game;

class Ball : public MovePiece
{
	public:
		Ball(Game* game, int x, int y, int z, double facingAngle);
		
		void update();
		Game* mGame;

	private:

};

#endif
