#ifndef BASEPIECE_H
#define BASEPIECE_H

#include "common/2d/vector2d.h"

class BasePiece
{
	public:
		BasePiece(int x, int y, int z, double diameter);
		
		void update();

                Vector2D mStartPosition;
                Vector2D mPosition;
		double mDiameter;


		//id
                int mId;
		static int mNextId; 
		void setId(int id);	

};

#endif

