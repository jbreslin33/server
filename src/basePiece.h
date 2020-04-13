#ifndef BASEPIECE_H
#define BASEPIECE_H

#include "common/2d/vector2d.h"

class BasePiece
{
	public:
		BasePiece(int x, int y, int z);
		
		void update();

                Vector2D mPosition;

		//id
                int mId;
		static int mNextId; 
		void setId(int id);	

};

#endif

