



#include "WSocketSet.h"


WSocketSet::WSocketSet()
{

}



WSocketSet::~WSocketSet()
{


}






bool WSocketSet::addSocket(WSocket *socket)
{

	sockets.push_back(socket);

	//cout << "add socket" << endl;

 	vector<WSocket *>::iterator socketIterator;

	for(socketIterator=sockets.begin();socketIterator!=sockets.end();socketIterator++)
		{
			//cout << "comp socket" << endl;
			if(*(*socketIterator) == (*socket))
				{
					cout << "true" << endl;
				}
		}
	

	return true;


}



