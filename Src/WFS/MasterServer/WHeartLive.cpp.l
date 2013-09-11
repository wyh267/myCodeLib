

#include "WHeartLive.h"

#include "WNetWorkService.h"

#include <iostream>


WHeartLive::WHeartLive(const char *m_name,int port)
CThread(m_name)
{

	port_=port;

}




WHeartLive::~WHeartLive()
{

}

		

void WHeartLive::mainLoop()
{

	SConnect_t *rec_info;

	WNetWorkService *nw=new WNetWorkService(true,port_,20);

	nw->startService();

	while(1)
		{

			if(nw->recivePacket(&rec_info)==true)
				{

					cout << "Got Data..." << endl;


				}
			

		}





}



