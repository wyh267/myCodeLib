


#include <iostream>
#include <string>
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include "WNetWorkService.h"

#include "WSocketSet.h"
#include "WSocket.h"

using namespace std;


int main()
{

#if 1
	SConnect_t *rec_info;

	WNetWorkService *nw=new WNetWorkService(true,40239,20);

	

	nw->startService();


	//sleep(5);

	while(1)
		{
			if(nw->recivePacket(&rec_info)==true)
				{
					//string *str=new string(rec_info->data);
					;//rec_info->data[rec_info->data_len]='\0';
					cout << " ECHO SERVER  ===] " << rec_info->data<< endl;//<< rec_info->data << endl;
					//for(int i=0;i<rec_info->data_len;i++)
					//	cout << rec_info->data[i];
				
				}
	//		
			
		}

	

	

#endif
#if 0
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











