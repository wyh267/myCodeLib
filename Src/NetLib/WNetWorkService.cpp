


#include "WNetWorkService.h"

#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


WNetWorkService::WNetWorkService(bool server,int port_num,int max_listen)
{

	server_=server;
	port_num_=port_num;
	max_listen_=max_listen;


}


WNetWorkService::~WNetWorkService()
{


}




ServiceCode WNetWorkService::startService()
{

	if(server_==false)
		{
			cout << " This service must be a server...you chose client mode ..." << endl;
			return kFail;
		}



	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr)); 
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port_num_);
	// time_t now;
	
	
	int server_socket = socket(AF_INET,SOCK_STREAM,0);
	
	if( server_socket < 0)
	{
		cout << "Create Socket Failed!" << endl;;
		return kSocketError;
	}

	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		cout << "Server Bind Port : " << port_num_ << " Failed!" << endl;
		return kBindingError;
	}

	
	if (listen(server_socket, max_listen_))
	{
		cout << "Server Listen Failed!" << endl;
		return kLiseningError;
	}


	cout << " Start the service success..." << endl;

	socket_list_.push_back(server_socket);


	p_recive_thread=new WNetReciveThread("Recive Thread");
	p_recive_thread->configureReciveThread(server_socket);
	p_recive_thread->run();
	p_recive_thread->startReciveThread();
	
	return kSuccess;

}




