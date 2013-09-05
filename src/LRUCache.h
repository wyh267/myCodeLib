/*

	LRU Cache

*/

#ifndef _LRUCACHE_
#define _LRUCACHE_


#include <iostream>
#include <string>

using namespace std;

typedef struct _Node_{

	int key;
	int value;
	
	struct _Node_ *next;
	struct _Node_ *pre;

}CacheNode;



class LRUCache{
	
public:
	
	LRUCache(int cache_size=10);  
	~LRUCache();


	int getValue(int key);	
	bool putValue(int key,int value);	
	void displayNodes();
	
	
private:
	
	int cache_size_;
	int cache_real_size_;
	CacheNode *p_cache_list_head;
	CacheNode *p_cache_list_near;
		
	void detachNode(CacheNode *node);
	void addToFront(CacheNode *node);

};



#endif
