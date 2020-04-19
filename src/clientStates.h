#ifndef CLIENTSTATES_H
#define CLIENTSTATES_H

#include "clientState.h"

class Client;

class GlobalClientState : public ClientState
{

	public:
		GlobalClientState();

 		void enter(Client* client);
 		void execute(Client* client);
 		void exit(Client* client);
};

class InitClientState : public ClientState
{

	public:
		InitClientState();

 		void enter(Client* client);
 		void execute(Client* client);
 		void exit(Client* client);
};

class WaitClientState : public ClientState
{

	public:
		WaitClientState();

 		void enter(Client* client);
 		void execute(Client* client);
 		void exit(Client* client);
};



class HumanClientState : public ClientState
{

	public:
		HumanClientState();

 		void enter(Client* client);
 		void execute(Client* client);
 		void exit(Client* client);
};



class ChaseBallClientState : public ClientState
{

	public:
		ChaseBallClientState();

 		void enter(Client* client);
 		void execute(Client* client);
 		void exit(Client* client);
};





#endif
