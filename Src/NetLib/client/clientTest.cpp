


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
	serv_addr.sin_port=htons(22);
	cout << "OK" << endl;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.0.1");//ipaddr.c_str()); //inet_addr×ª»»ÎªÍøÂç×Ö½ÚÐò
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
		return false;
		}
	else
		{
		cout << "OK" << endl;
		return true;
		}
	
	return true;
	#endif

	


#if 1
	SConnect_t *rec_info;
	SConnect_t *conn;

	WNetWorkService *nw=new WNetWorkService(true,40239,20);

	

	//nw->startService();


	//sleep(5);

	string ip="192.168.0.74";
	conn=nw->connectToServer(40239,ip.c_str());
	string data="ABCDEDFADFDSFADSFEFDASF";
	strcpy(conn->data,data.c_str());
	conn->data_len=24;
	cout << " Success " << endl;

	cout << " close : " << conn->socket_fd << endl;
	//sleep(3);

	nw->sendPacket(conn);

	nw->sendPacket(conn);

	nw->sendPacket(conn);

	nw->sendPacket(conn);

	nw->sendPacket(conn);

	//nw->closeSocket(conn);

	
	while(1);

	

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











