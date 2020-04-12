#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "basePiece.h"

class Client;

class MovePiece : public BasePiece
{
	public: 
		MovePiece(Client* client, int x, int y, int z);

 		void update();

                Client* mClient;
                Vector3d* mVelocity;

                double mSpeed;


};

#endif
