

#include "CLinuxMsgQueue.h"
#include "COperatingSystemFactory.h"

#include <iostream>

using namespace std;

CLinuxMsgQueue::CLinuxMsgQueue(const char *pName):
CMsgQueue(pName)
{

	p_mutex=COperatingSystemFactory::newMutex("Msg Mutex");
	p_sem=COperatingSystemFactory::newCountingSem(0);


	pthread_mutex_init(&mutex, NULL);  
    	pthread_cond_init(&cond, NULL);  
	count=0;

}



CLinuxMsgQueue::~CLinuxMsgQueue()
{

}





bool CLinuxMsgQueue::recvMsg(unsigned int &m_msg_code,void *&p_msg)
{

 	bool result;
    	Elements queue_element;
		
		#if 1

	 pthread_mutex_lock(&mutex);
	 if(count==0)
	 	{
        	pthread_cond_wait(&cond,&mutex);/*µÈ´ý*/
		count--;
	 	}
        pthread_mutex_unlock(&mutex);
	p_mutex->Lock();

   
	if (m_queue.empty()) {
	    
		p_mutex->UnLock();
	    	return false;
	    
	}

	queue_element = m_queue.front();
	m_queue.pop_front();


	m_msg_code = queue_element.msg_code;
	p_msg = queue_element.p_message;
	p_mutex->UnLock();
	#endif
    return true;


}




bool CLinuxMsgQueue::sendMsg(unsigned int m_msg_code,void *p_msg)
{
	bool result;
    	Elements queue_element;
	if(m_queue.size()==32)
		{
			cout << " fail..." << endl;
			return false;
		}
	
	queue_element.msg_code=m_msg_code;
	queue_element.p_message=p_msg;
	p_mutex->Lock();

	m_queue.push_back(queue_element);
	//p_sem->Post();
	pthread_mutex_lock(&mutex);
	if(count==0)
		count++;
        pthread_cond_broadcast(&cond);
		//cout << " send..." << endl;
        pthread_mutex_unlock(&mutex);
	p_mutex->UnLock();


    return true;


}


