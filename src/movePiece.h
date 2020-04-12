#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include "basePiece.h"

class Client;

class MovePiece : public BasePiece
{
	public: 
		MovePiece(Client* client, int id, int x, int y, int z);
};

#endif
