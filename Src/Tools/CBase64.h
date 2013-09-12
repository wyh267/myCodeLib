


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



	static string encodeBase64(unsigned char *input , int input_len);

	static string decodeBase64(string input);


	static int indexOfCode(const char c);



};






#endif




