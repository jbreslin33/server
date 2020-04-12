#ifndef BALL_H
#define BAL_H

#include "movePiece.h"

class Ball : public MovePiece
{
	public:
		Ball(int x, int y, int z);
		
		void update();

	private:

};

#endif
