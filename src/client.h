#ifndef CLIENT_H
#define CLIENT_H

class Client
{
	public:
		Client(int id);

		void setId(int id);
		int getId();
	private:

		int mId;


};

#endif
