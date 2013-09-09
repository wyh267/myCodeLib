


#include "WSocket.h"


WSocket::WSocket(int socket)
{
	socket_fd_=socket;
}



WSocket::~WSocket()
{


}


bool WSocket::operator == (const WSocket &otherInstance) const
{
	cout << " comp " << socket_fd_ << endl;
	
	if(socket_fd_==otherInstance.socket_fd_)
		return true;
	else
		return false;

}



