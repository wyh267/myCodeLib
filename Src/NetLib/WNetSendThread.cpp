


#include "WNetSendThread.h"


#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket


#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>


WNetSendThread::WNetSendThread(const char *m_name):
CThread(m_name)
{

	//add your code here
	p_control_msg_=COperatingSystemFactory::newMsgQueue("control message for revice thread");
	
	

}



WNetSendThread::~WNetSendThread()
{

}




bool WNetSendThread::sendPacket(SConnect_t *packet)
{
	int sent_len=0;
	
	cout << "send packet :" << packet->socket_fd <<  endl;

	
	int ret=send(packet->socket_fd,packet->data,packet->data_len,0);

	//cout << "ret :" << ret  << "  packet->data_len :" << packet->data_len<< endl;
	if(ret <= 0)
		return false;
	else
		sent_len+=ret;

	

	
	while(sent_len < packet->data_len)
		{
			cout << "send ag" << endl;
			ret=send(packet->socket_fd,packet->data+sent_len,packet->data_len-sent_len,0);
			if(ret <= 0)
				return false;
			else
				sent_len+=ret;
			
		}

	return true;

	

}



void WNetSendThread::sendData(SConnect_t *data)
{
	unsigned int code=0;
	p_control_msg_->sendMsg(code,(void *)data);

}



void WNetSendThread::mainLoop()
{
	unsigned int code;
	void *p_msg;
	//cout << " Recive msg " << endl;
	while(1)
		{
			//cout << " Recive msg " << endl;
			p_control_msg_->recvMsg(code, p_msg);
			if(sendPacket((SConnect_t *) p_msg)==false)
				{
				cout << "send fail" << endl;
				p_control_msg_->sendMsg(code,p_msg);
				}

		}


}








