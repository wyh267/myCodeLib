

#ifndef _WSOCKET_
#define _WSOCKET_


#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket

#include <string.h>


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



class WSocket{
	
public:
	WSocket();
	WSocket(int socket_num);
	~WSocket();
	
	bool configureSocket(int port_num=26719,int max_listen=20);


	bool bindingSocket();

	bool listeningSocket();

	WSocket* acceptSocket();
	
	
	bool sendPacketAsync();
	
	bool sendPacketSync();
	
	bool recivePacketSync();
	
	
	bool closeSocket();

	 bool operator == (const WSocket &otherInstance) const;
	
//private:
	
	int server_socket;
	
private:

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t length;

	int port_num_;
	int max_listen_;

	int new_server_socket;



};










#endif


