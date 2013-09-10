

#ifndef _WNETWORKSERVICE_H_
#define _WNETWORKSERVICE_H_

#include <vector>
#include <string>

#include "WNetReciveThread.h"
#include "WNetSendThread.h"

#include "CMsgQueue.h"
#include "COperatingSystemFactory.h"

using namespace std;

typedef enum 
{
	kSuccess,
	kFail,
	kSocketError,
	kBindingError,
	kAcceptError,
	kLiseningError,
	kConnectError

}ServiceCode;




class WNetWorkService
{

public:

	WNetWorkService(bool server=true,int port_num=26719,int max_listen=20);
	~WNetWorkService();


	ServiceCode startService();

	bool configureService();


	bool recivePacket(SConnect_t **info,int timeout_ms=0);

	bool sendPacket(SConnect_t *info);

	SConnect_t* connectToServer(int port_num,const char * ipaddr);

	bool closeSocket(SConnect_t *conn);




private:

	int port_num_;
	bool server_;
	int max_listen_;

	bool client_is_start_;

	WNetReciveThread *p_recive_thread;
	WNetSendThread   *p_send_thread;

	CMsgQueue *p_recive_msg_;
	

	vector<int> socket_list_;
	vector<int> socket_recive_list_;
	vector<int> socket_send_list_;




};
















#endif




