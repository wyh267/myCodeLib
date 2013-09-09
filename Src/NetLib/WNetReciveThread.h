

#ifndef _WNETRECIVETHREAD_H_
#define _WNETRECIVETHREAD_H_


#include "CThread.h"
#include "CMsgQueue.h"
#include "COperatingSystemFactory.h"

#include <vector>

using namespace std;

typedef enum
{

	kStart,
	kStop,
	kPause,
	kCheck

}NetReciveStatusCode;



typedef struct _data_
{
	char data[1024];
	int    data_len;

}SData;



typedef struct _connect_info_ {

	int			  socket_fd;
	vector<SData> data_list;


}SConnect_t;





class WNetReciveThread:public CThread
{

	public:
		WNetReciveThread(const char *m_name);
		~WNetReciveThread();

		bool configureReciveThread(int server_socket);

		void startReciveThread();
		

		virtual void mainLoop();

		

	private:

		CMsgQueue *p_control_msg_;

		vector<int>  socket_list_;
		int server_socket_;
		int max_socket_;


		void checkSelectSocket();

};








#endif



