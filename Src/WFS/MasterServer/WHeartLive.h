
#ifndef _WHEARTLIVA_H_
#define _WHEARTLIVA_H_


#include "CThread.h"

using namespace std;


class WHeartLive:public CThread
{

	public:
		WHeartLive(const char *m_name,int port=26719);
		~WHeartLive();

		

		virtual void mainLoop();

		

	private:

		int port_;
		

};







#endif




