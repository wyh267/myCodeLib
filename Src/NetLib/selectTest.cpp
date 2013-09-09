

#if 0
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#endif
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "WNetWorkService.h"

using namespace std;

#define HELLO_WORLD_SERVER_PORT 26719
#define LENGTH_OF_LISTEN_QUEUE 2
int main()
{


	WNetWorkService *nw=new WNetWorkService();

	nw->startService();


#if 0
	vector<int> connection;
	char buf[3];
	
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr)); //把一段内存区的内容全部设置为0
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
	// time_t now;
	
	
	int server_socket = socket(AF_INET,SOCK_STREAM,0);
	
	if( server_socket < 0)
	{
	printf("Create Socket Failed!");
	exit(1);
	}

	if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
	printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
	exit(1);
	}

	//server_socket用于监听
	
	if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
	{
	printf("Server Listen Failed!");
	exit(1);
	}
	
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	fd_set fdsr;
	struct timeval tv;
	int ret=0;
	int maxsocket=server_socket;
	while(1)
	{
		FD_ZERO(&fdsr);
		FD_SET(server_socket, &fdsr);
		
		for (int i = 0; i < connection.size(); i++) {
		   if (connection[i] != 0) {
		       FD_SET(connection[i], &fdsr);
		   }
		}

		// timeout setting
		tv.tv_sec = 30;
		tv.tv_usec = 0;
				
		ret = select(maxsocket + 1, &fdsr, NULL, NULL, &tv);
		if (ret < 0) {
		    perror("select");
		   break;
		} else if (ret == 0) {
		   printf("timeout\n");
		   continue;
		}
		
		for (int i = 0; i < connection.size(); i++)
		{
			if(FD_ISSET(connection[i],&fdsr))
			{
				ret = recv(connection[i], buf, sizeof(buf), 0);
				     if (ret <= 0) {        // client close
				          printf("client[%d] close\n", i);
				         // close(connection[i]);
				                    FD_CLR(connection[i], &fdsr);
				                    connection[i] = 0;
				                } else {        // receive data
				                    if (ret < 512)
				                        memset(&buf[ret], '\0', 1);
				                    printf("client[%d] send:%s\n", i, buf);
				                }
			}
		}
		
		if (FD_ISSET(server_socket, &fdsr))
		{
				
		
			int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
			if ( new_server_socket < 0)
			{
				printf("Server Accept Failed!\n");
			}
			cout << "Get Socket Connect . Socket Number is : [ " << new_server_socket <<" ] " << endl;
			connection.push_back(new_server_socket);
			if(maxsocket<new_server_socket)
				maxsocket=new_server_socket;
			
			cout << "max :" << maxsocket  << " new_socket " << new_server_socket << endl;
		}
		
	}
	
	
	
	
	
#endif	
	
	while(1);
	
	return 1;
}











