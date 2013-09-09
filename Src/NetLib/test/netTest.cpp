


#include <iostream>

#include "WNetWorkService.h"

#include "WSocketSet.h"
#include "WSocket.h"

using namespace std;


int main()
{
#if 0
	SConnect_t *rec_info;

	WNetWorkService *nw=new WNetWorkService(true,40239,20);

	nw->startService();

	while(1)
		{
			nw->recivePacket(rec_info);
			
			
		}

#endif
#if 1
	WSocket *a=new WSocket(1);
	WSocket *b=new WSocket(2);
	WSocket *c=new WSocket(3);
	WSocket *d=new WSocket(4);

	WSocketSet *s=new WSocketSet();

	s->addSocket(a);
	s->addSocket(b);
	s->addSocket(c);
	s->addSocket(d);

	s->addSocket(a);
	s->addSocket(a);
	s->addSocket(a);
#endif
	return 1;
}











