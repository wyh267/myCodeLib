


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
#if 0
	struct sockaddr_in serv_addr;
	bzero(&serv_addr,sizeof(serv_addr)); 

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(40239);
	cout << "OK" << endl;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.0.74");//ipaddr.c_str()); //inet_addr×ª»»ÎªÍøÂç×Ö½ÚÐò
	cout << "OK" << endl;
	bzero(&(serv_addr.sin_zero),8);

	cout << "OK" << endl;
	int server_socket = socket(AF_INET,SOCK_STREAM,0);
	if( server_socket < 0)
	{
		cout << "Create Socket Failed!" << endl;;
		return false;
	}else
		cout << "socket success " << server_socket << endl;

	cout << "OK" << endl;
	if ( connect( server_socket, ( struct sockaddr *)&serv_addr , sizeof(struct sockaddr)) < 0 )
		{
		cout << "OK1" << endl;
		}
	else
		{
		cout << "OK" << endl;
		}
	

	char sdata[1024];
	string data="ABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASFABCDEDFADFDSFADSFEFDASF";
	strcpy(sdata,data.c_str());

	int ret;
	while(1)
		{
		usleep(100);
		ret=send(server_socket,sdata,240,0);
		}
		#endif
#if 1
	SConnect_t *rec_info;
	SConnect_t *conn;
	vector<WNetWorkService *> nwl;
	vector<SConnect_t *> conns;

	string ip="192.168.0.74";
	string data="ABCDEDFADFDSFADSFEFDASF";
	
	for(int i=0;i<5;i++)
		{
			WNetWorkService *nw=new WNetWorkService(true,40239,20);
			conn=nw->connectToServer(40239,ip.c_str());
			strcpy(conn->data,data.c_str());
			conn->data_len=24;
			nwl.push_back(nw);
			conns.push_back(conn);
		}

	


	
	sleep(1);
	//sleep(3);

	for(int i=0;i<nwl.size();i++)
			{
				cout << conns[i]->socket_fd << endl;
				if(nwl[i]->sendPacket(conns[i])==false)
					cout << "send fail..." << endl;
			}
	sleep(2);
	while(1)
		{
		//cout << " close : " << conn->socket_fd << endl;
			for(int i=0;i<nwl.size();i++)
				{
					if(nwl[i]->recivePacket(&rec_info)==true)
						{
							//cout << "Got data " << endl;
							//SConnect_t *t=new SConnect_t();
							//t->socket_fd=rec_info->socket_fd;
							//strcpy(t->data,data.c_str());
							//t->data_len=24;
							//free( rec_info);
							    delete rec_info;
							//rec_info=NULL;
							nwl[i]->sendPacket(conns[i]);
						}
				}
		
			
		//usleep(20);
		}


	
	while(1)
		sleep(10);

	

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











