


#ifndef _WSOCKETSET_H_
#define _WSOCKETSET_H_


#include <vector>

#include "WSocket.h"

using namespace std;

class WSocketSet
{

public:

	WSocketSet();
	~WSocketSet();


	bool addSocket(WSocket *socket);




private:

	vector<WSocket *>  sockets;



};








#endif



