

#ifndef _WSOCKET_
#define _WSOCKET_





class WSocket{
	
public:
	WSocket();
	~WSocket();
	
	bool configureSocket();
	
	bool sendPacketAsync();
	
	bool sendPacketSync();
	
	bool recivePacketSync();
	
	
	bool closeSocket();
	
private:
	
	int socket_fd_
	
	



};







#endif


