


#include "WNetWorkService.h"

#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


WNetWorkService::WNetWorkService(bool server,int port_num,int max_listen)
{

	server_=server;
	port_num_=port_num;
	max_listen_=max_listen;
	client_is_start_=false;
	p_recive_msg_=COperatingSystemFactory::newMsgQueue("recive message for revice thread");
	
	


}


WNetWorkService::~WNetWorkService()
{


}



SConnect_t* WNetWorkService::connectToServer(int port_num,const char * ipaddr)
{

	SConnect_t *conn=new SConnect_t();
	conn->socket_fd=-1;

	struct sockaddr_in serv_addr;
	bzero(&serv_addr,sizeof(serv_addr)); 

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(port_num);
	serv_addr.sin_addr.s_addr = inet_addr(ipaddr);//.c_str()); //inet_addr×ª»»ÎªÍøÂç×Ö½ÚÐò
	bzero(&(serv_addr.sin_zero),8);

	cout << "OK" << endl;
	int clinet_socket = socket(AF_INET,SOCK_STREAM,0);
	if( clinet_socket < 0)
	{
		cout << "Create Socket Failed!" << endl;;
		//return false;
	}else
		cout << "socket success " << clinet_socket << endl;

	if ( connect( clinet_socket, ( struct sockaddr *)&serv_addr , sizeof(struct sockaddr)) < 0 )
		{
			;//return false;
		}
	else
		{
			conn->socket_fd=clinet_socket;//return true;
		}

	socket_list_.push_back(clinet_socket);

	if(client_is_start_==false)
		{
			client_is_start_=true;
			p_recive_thread=new WNetReciveThread("Recive Thread");
			p_recive_thread->configureReciveThread(0,p_recive_msg_,clinet_socket);
			p_recive_thread->run();
			p_recive_thread->startReciveThread();


			p_send_thread=new WNetSendThread("Send Thread");
			p_send_thread->run();
		}
	
	return conn;
	
}




ServiceCode WNetWorkService::startService()
{
	if(server_==false)
		{
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
	p_recive_thread->configureReciveThread(server_socket,p_recive_msg_);
	p_recive_thread->run();
	//sleep(5);
	p_recive_thread->startReciveThread();


	p_send_thread=new WNetSendThread("Send Thread");
	p_send_thread->run();
	
	return kSuccess;

}




bool WNetWorkService::sendPacket(SConnect_t *info)
{

	//p_send_thread->sendData(info);
	#if 0
	fd_set fdsr;
	struct timeval tv;
	int ret=0;
	int sent=0;
	

	FD_ZERO(&fdsr);
	FD_SET(info->socket_fd,&fdsr);

	tv.tv_sec = 3;
	tv.tv_usec = 0;
	//cout << "socket " << info->socket_fd <<endl;
	if ((ret=select(info->socket_fd+1, NULL, &fdsr, NULL, &tv)) > 0) 
	{ 

		if (ret < 0) {
		    cout << "select error" << endl;
		   return false;
		} else if (ret == 0) {
		cout << "select error0" << endl;
		   return false;
		}
		if (FD_ISSET(info->socket_fd, &fdsr)) 
			sent = send(info->socket_fd,info->data,info->data_len,0);
	}

	#endif
	send(info->socket_fd,info->data,info->data_len,0);
	
	//p_send_thread->sendPacket(info);
	//delete info;
	return true;

}


bool WNetWorkService::recivePacket(SConnect_t **info,int timeout_ms)
{
	unsigned int m_msg_code;
	void *p_msg;
	p_recive_msg_->recvMsg(m_msg_code, p_msg);
	*info=(SConnect_t *)p_msg;

	if(m_msg_code==kGotData)
		{

			//info->data[info->data_len]='\0';
			//cout <<" client " << (*info)->socket_fd << " sendlen :" <<  (*info)->data_len << " data " <<(*info)->data << endl;

			//p_send_thread->sendData(info);
			return true;
		}

	if(m_msg_code == kConnectClosed)
		{
			cout << " Connect " << (*info)->socket_fd << " is Closed" << endl;
			return false;
		}

	return true;

}



bool WNetWorkService::closeSocket(SConnect_t *conn)
{
	if(conn->socket_fd!=-1)
		{
			close(conn->socket_fd);
			return true;
		}

	return false;

}


