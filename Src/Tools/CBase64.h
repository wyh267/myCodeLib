


#ifndef _CBASE64_H_
#define _CBASE64_H_


#include <iostream>
#include <string>


using namespace std;


class CBase64
{

public:
	CBase64();
	~CBase64();



	static string encodeBase64(string input);

	static string decodeBase64(string input);




};






#endif




