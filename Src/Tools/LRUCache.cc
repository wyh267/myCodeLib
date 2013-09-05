

#include "LRUCache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <hash_map>
#if __GNUC__>2
#include <ext/hash_map>
using __gnu_cxx::hash_map;
#else
#include <hash_map>
#endif


LRUCache::LRUCache(int cache_size)
{
	cache_size_=cache_size;
	cache_real_size_=0;
	p_cache_list_head=new CacheNode();
	p_cache_list_near=new CacheNode();
	p_cache_list_head->next=p_cache_list_near;
	p_cache_list_head->pre=NULL;
	p_cache_list_near->pre=p_cache_list_head;
	p_cache_list_near->next=NULL;
	
}

LRUCache::~LRUCache()
{
	CacheNode *p;
	p=p_cache_list_head->next;
	while(p!=NULL)
	{	
		delete p->pre;
		p=p->next;
	}

	delete p_cache_list_near;
	
}


void LRUCache::detachNode(CacheNode *node)
{
	node->pre->next=node->next;
	node->next->pre=node->pre;
}

void LRUCache::addToFront(CacheNode *node)
{
	node->next=p_cache_list_head->next;
	p_cache_list_head->next->pre=node;
	p_cache_list_head->next=node;
	node->pre=p_cache_list_head;
}


int LRUCache::getValue(int key)
{
	CacheNode *p=p_cache_list_head->next;	
	while(p->next!=NULL)
	{
		
		if(p->key == key) //catch node
		{
			
			detachNode(p);
			addToFront(p);
			return p->value;
		}	
		p=p->next;	
	}
	return -1;
}



bool LRUCache::putValue(int key,int value)
{
	CacheNode *p=p_cache_list_head->next;
	while(p->next!=NULL)
	{
		
		
		if(p->key == key) //catch node
		{
			p->value=value;
			getValue(key);
			return true;
		}	
		p=p->next;	
	}
	
	
	if(cache_real_size_ >= cache_size_)
	{
		cout << "free" <<endl;
		p=p_cache_list_near->pre->pre;
		delete p->next;
		p->next=p_cache_list_near;
		p_cache_list_near->pre=p;
	}
	
	p=new CacheNode();//(CacheNode *)malloc(sizeof(CacheNode));
	
	if(p==NULL)
		return false;

	addToFront(p);
	p->key=key;
	p->value=value;
		
	cache_real_size_++;
		
	return true;	
}


void LRUCache::displayNodes()
{
	CacheNode *p=p_cache_list_head->next;
	
	while(p->next!=NULL)
	{
		cout << " Key : " << p->key << " Value : " << p->value << endl; 
		p=p->next;
		
	}
	cout << endl;
	
}


int main()
{
	
	LRUCache *cache=new LRUCache(9);
	
	cache->putValue(1,1);
	cache->putValue(2,2);
	cache->putValue(3,3);
	cache->putValue(4,3);
	cache->putValue(5,2);
	cache->displayNodes();
	
	cout << cache->getValue(4) << endl;
	cache->displayNodes();
	//cache->displayNodes();
	cout << cache->getValue(3) << endl;	
	cache->displayNodes();
	cout << cache->getValue(3) << endl;	
	cache->displayNodes();
	cout << cache->getValue(1) << endl;	
	cache->displayNodes();
	cout << cache->getValue(2) << endl;
	cache->displayNodes();	
	cout << cache->getValue(9) << endl;	
	
	cache->displayNodes();
	
	cache->putValue(4,9);
	//cout << cache->getValue(2) << endl;
	//cout << cache->getValue(3) << endl;
	cache->displayNodes();
	cout << cache->getValue(4) << endl;	
	cache->displayNodes();
	cout << cache->getValue(2) << endl;	
	cache->displayNodes();
	
	delete cache;
	
	return 1;
}









