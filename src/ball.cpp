#include "ball.h"

Ball::Ball(Game* game, int x, int y, int z, double facingAngle, double diameter) : MovePiece(x,y,z,facingAngle, diameter)
{
	mGame = game;
}
