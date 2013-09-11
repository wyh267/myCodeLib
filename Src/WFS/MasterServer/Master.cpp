


#include <iostream>
#include <vector>
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
	int flag=1;
	vector<SConnect_t *> connects;
	vector<SConnect_t *>::iterator connectsIt;;
	string data="ABCDEDFADFDSFADSFEFDASF";

	SConnect_t *rec_info;
	SConnect_t *send=new SConnect_t();

	WNetWorkService *nw=new WNetWorkService(true,40239,20);

	nw->startService();

	strcpy(send->data,data.c_str());
	send->data_len=24;
	//sleep(5);

	while(1)
		{
			if(nw->recivePacket(&rec_info)==true)
				{
					//if(flag==1)
					//	{
							send->socket_fd=rec_info->socket_fd;
							//flag=0;
					//	}
					//string *str=new string(rec_info->data);
					;//rec_info->data[rec_info->data_len]='\0';
					//cout << " ECHO SERVER  ===] " << rec_info->data<< endl;//<< rec_info->data << endl;
					/*bool flag=false;
					for(connectsIt=connects.begin();connectsIt!=connects.end();connectsIt++)
						{
							if((*connectsIt)->socket_fd == rec_info->socket_fd)
								{
									//cout << "the Same" << endl;
									flag=true;
								}
						}

					if(flag==false)
						connects.push_back(rec_info);*/
					
					//for(int i=0;i<rec_info->data_len;i++)
					//	cout << rec_info->data[i];
					//cout << "GOT" << rec_info->data_len <<endl;
					nw->sendPacket(send);
					//delete rec_info;
				
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











