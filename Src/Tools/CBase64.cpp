




#include "CBase64.h"

#include <string.h>

CBase64::CBase64()
{
}
CBase64::~CBase64()
{

}



string CBase64::encodeBase64(string input)
{
	string code="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned char input_char[3];
	char output_char[4];
	int output_num;
	string output_str="";
	int near=input.size()%3;

	cout<< " input : " << input << endl;

	for(int i=0;i<input.size();i+=3)
		{
			memset(input_char ,0,3);
			memset(output_char ,61,4);
			if((i+3) <= input.size())
				{
					input.copy((char *)input_char,3,i);
				}else
					{
						
						input.copy((char *)input_char,input.size()-i,i);
						cout << input_char << endl;
						output_num=((int)input_char[0]<<16)+((int)input_char[1]<<8)+(int)input_char[2];
						if(near==1)
							{
							output_char[0]=code[((output_num>>18) & 0xff)];
							output_char[1]=code[((output_num>>12) & 0x3f)];
							output_char[2]='=';
							output_char[3]='=';
							}

						if(near==2)
							{
							output_char[0]=code[((output_num>>18) & 0xff)];
							output_char[1]=code[((output_num>>12) & 0x3f)];
							output_char[2]=code[((output_num>>6) & 0x3f)];;
							output_char[3]='=';
							}
						output_str.append(output_char);
						break;
					}

			output_num=((int)input_char[0]<<16)+((int)input_char[1]<<8)+(int)input_char[2];
			output_char[0]=code[((output_num>>18) & 0xff)];
			output_char[1]=code[((output_num>>12) & 0x3f)];
			output_char[2]=code[((output_num>>6) & 0x3f)];
			output_char[3]=code[((output_num) & 0x3f)];
			output_str.append(output_char);
			
		}
	
	cout <<"encode Base64 :" << output_str <<  endl;

	return output_str;


}


int CBase64::indexOfCode(const char c)
{
	string code="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	for(int i=0;i<code.size();i++)
		{
			if(code[i]==c)
				return i;
		}
	return 0;
}


string CBase64::decodeBase64(string input)
{
	
	unsigned char input_char[4];
	unsigned char output_char[3];
	int output_num=0;
	int k=0;
	string output_str="";
	//cout << input.size() << endl;
	for(int i=0;i<input.size();i++)
		{
			//cout <<hex << input[i];
			input_char[k]=indexOfCode(input[i]);
			k++;
			if(k==4)
				{
					cout << endl;
					output_num= ((int)input_char[0]<<18)+((int)input_char[1]<<12)+((int)input_char[2]<<6)+((int)input_char[3]);
					//cout << hex << (int)input_char[0] <<" " << hex << (int)input_char[1] <<" " << hex << (int)input_char[2] <<" " << hex << (int)input_char[3] <<endl;
					//cout << hex <<output_num << endl;
					output_char[0]=(unsigned char)(output_num >> 16) ;
					output_char[1]=(unsigned char)(output_num >> 8) ;
					output_char[2]=(unsigned char)(output_num ) ;

					output_str.append((char *)output_char);
					k=0;
				}
		}

	cout << output_str << endl;
	return output_str;


}



