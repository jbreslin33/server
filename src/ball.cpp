#include "ball.h"

Ball::Ball(Game* game, int x, int y, int z) : MovePiece(x,y,z)
{
	mGame = game;
}
