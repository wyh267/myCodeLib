

#ifndef _WSOCKET_
#define _WSOCKET_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



class WSocket{
	
public:
	WSocket(int socket);
	~WSocket();
	
	bool configureSocket();
	
	bool sendPacketAsync();
	
	bool sendPacketSync();
	
	bool recivePacketSync();
	
	
	bool closeSocket();

	 bool operator == (const WSocket &otherInstance) const;
	
//private:
	
	int socket_fd_;
	
	



};










#endif


