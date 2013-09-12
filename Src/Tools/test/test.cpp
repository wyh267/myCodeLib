
#include <iostream>
#include "LRUCache.h"
#include "CBase64.h"

int main()
{
	#if 0
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
	#endif

	string input="Man is distinguished";//, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure..";
	string base64= "TWFuIGlzIGRpc3Rpbmd1aXNoZWQ=";//= CBase64::encodeBase64(input);
	CBase64::decodeBase64(base64);


	
	return 1;
}