


#include <iostream>

#include "WNetWorkService.h"

using namespace std;


int main()
{

	SConnect_t *rec_info;

	WNetWorkService *nw=new WNetWorkService(true,40239,20);

	nw->startService();

	while(1)
		{
			nw->recivePacket(rec_info);
			
			
		}


	
	return 1;
}











