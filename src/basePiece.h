#ifndef BASEPIECE_H
#define BASEPIECE_H

class Vector3d;

class BasePiece
{
	public:
		BasePiece(int x, int y, int z);
		
		void update();

                Vector3d* mPosition;

		//id
                int mId;
		static int mNextId; 
		void setId(int id);	

};

#endif

