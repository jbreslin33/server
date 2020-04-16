#include "ball.h"

Ball::Ball(Game* game, int x, int y, int z, double facingAngle) : MovePiece(x,y,z,facingAngle)
{
	mGame = game;
}
