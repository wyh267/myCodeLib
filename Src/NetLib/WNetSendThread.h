

#ifndef _WNETSENDTHREAD_H_
#define _WNETSENDTHREAD_H_


#include "CThread.h"
#include "CMsgQueue.h"
#include "COperatingSystemFactory.h"

#include "WNetReciveThread.h"



class WNetSendThread:public CThread
{

	public:
		WNetSendThread(const char *m_name);
		~WNetSendThread();

		bool configureSendThread(int server_socket,CMsgQueue *p_recive_msg);

		void startSendThread();
		

		virtual void mainLoop();


		void sendData(SConnect_t *data);

		bool sendPacket(SConnect_t *packet);

	private:

		CMsgQueue *p_control_msg_;

		

};






#endif



