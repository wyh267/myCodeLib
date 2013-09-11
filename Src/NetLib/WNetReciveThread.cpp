



#include "WNetReciveThread.h"


#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket


#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>


WNetReciveThread::WNetReciveThread(const char *m_name):
CThread(m_name)
{

	//add your code here
	p_control_msg_=COperatingSystemFactory::newMsgQueue("control message for revice thread");
	client_mode_=false;
	

}



WNetReciveThread::~WNetReciveThread()
{

}



void WNetReciveThread::startReciveThread()
{
	unsigned int code=kStart;
	cout << "start Server now ... " << endl;
	p_control_msg_->sendMsg(code,NULL);

}




void WNetReciveThread::checkSelectSocket()
{
	//char buf[1024];

	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
	fd_set fdsr;
	struct timeval tv;
	int ret=0;

	FD_ZERO(&fdsr);
	FD_SET(server_socket_,&fdsr);

	for (int i = 0; i < socket_list_.size(); i++) {
	   if (socket_list_[i] != 0) {
	       FD_SET(socket_list_[i], &fdsr);
	   }
	}

	tv.tv_sec = 3;
	tv.tv_usec = 0;
			
	ret = select(max_socket_+ 1, &fdsr, NULL, NULL, &tv);
	if (ret < 0) {
	    cout << "select error" << endl;
	   return ;
	} else if (ret == 0) {
	   return ;
	}


	for(vector<int>::iterator it=socket_list_.begin(); it!=socket_list_.end();)
	    {
		        if(FD_ISSET(*it,&fdsr))
		        {
				//cout << " Socket [" <<*it << " ] has data" << endl; 

				SConnect_t *connect_data=new SConnect_t();

				//SData *buf=new SData();
				
				
				ret = recv(*it, connect_data->data, sizeof(connect_data->data), 0);
				connect_data->socket_fd=(*it);
				//cout << "client1[ " << connect_data->socket_fd<< "] close" << endl;
				if (ret <= 0) {        // client close
					//cout << "client[ " << *it << "] close" << endl;
					close(*it);
					FD_CLR(*it, &fdsr);
					it = socket_list_.erase(it);
					//cout << "client[ " << connect_data->socket_fd<< "] close" << endl;
					p_recive_msg_->sendMsg(kConnectClosed,  (void *)connect_data);
					
				} else {        // receive data
				if (ret <= 1024)
					{
						
				    		//memset(&(connect_data->data[ret]), '\0', 1);
						connect_data->data_len=ret;
						p_recive_msg_->sendMsg(kGotData, (void *)connect_data);
					}
				//cout <<" client " << *it << " send:" <<  connect_data->data<< endl;
				++it;
				}
		        }
		        else
		        {
		            ++it;
		    }
	   }

	
	if ((client_mode_ == false )&&FD_ISSET(server_socket_, &fdsr))
	{
			
	
		int new_server_socket = accept(server_socket_,(struct sockaddr*)&client_addr,&length);
		if ( new_server_socket < 0)
		{
			cout << "Server Accept Failed!\n" << endl;
		}else
			{
			cout << "Get Socket Connect . Socket Number is : [ " << new_server_socket <<" ] " << endl;
			socket_list_.push_back(new_server_socket);
			if(max_socket_<new_server_socket)
				max_socket_=new_server_socket;
			}
		
	}
		


}



void WNetReciveThread::mainLoop()
{
	unsigned int code;
	void *p_msg;
	//cout << " Recive msg " << endl;
	while(1)
		{
			//cout << " Recive msg " << endl;
			p_control_msg_->recvMsg(code, p_msg);

			switch(code)
				{
				case kStart:
						{
							cout << " Start the server ..." << endl;
							p_control_msg_->sendMsg(kCheck,NULL);
							break;
					}

				case kCheck:
						{
							//cout << "Check the sockets ... " << endl;
							checkSelectSocket();
							p_control_msg_->sendMsg(kCheck,NULL);
							break;

					}
				default:
					break;

				}
			
		}


}


bool WNetReciveThread::configureReciveThread(int server_socket,CMsgQueue *p_recive_msg,int client_socket)
{

	if(client_socket==0)
		{
		server_socket_=server_socket;
		max_socket_=server_socket;
		}
	else
		{
		socket_list_.push_back(client_socket);
		max_socket_=client_socket; 
		client_mode_=true;
		cout << "add " << client_socket << endl;
		}
	
	p_recive_msg_=p_recive_msg;
	return true;

}




