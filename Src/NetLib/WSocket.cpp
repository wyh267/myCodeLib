


#include "WSocket.h"




WSocket::WSocket(int socket_num)
{

	server_socket=socket_num;
	
}

WSocket::WSocket()
{


}



WSocket::~WSocket()
{


}



bool WSocket::configureSocket(int port_num,int max_listen)
{

	port_num_=port_num;
	max_listen_=max_listen;
	bzero(&server_addr,sizeof(server_addr)); 
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port_num_);
	// time_t now;
	
	
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	if( server_socket < 0)
	{
		cout << "Create Socket Failed!" << endl;;
		return false;
	}

	return true;

}


bool WSocket::bindingSocket()
{
	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		cout << "Server Bind Port : " << port_num_ << " Failed!" << endl;
		return false;
	}

	return true;

}


bool WSocket::listeningSocket()
{

	if (listen(server_socket, max_listen_))
	{
		cout << "Server Listen Failed!" << endl;
		return false;
	}

	return true;

}


WSocket* WSocket::acceptSocket()
{
	length = sizeof(client_addr);
	int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
	if(new_server_socket < 0 )
		return NULL;
	WSocket *sock=new WSocket(new_server_socket);
	return sock;

}




bool WSocket::operator == (const WSocket &otherInstance) const
{
	cout << " comp " << server_socket << endl;
	
	if(server_socket==otherInstance.server_socket)
		return true;
	else
		return false;

}



