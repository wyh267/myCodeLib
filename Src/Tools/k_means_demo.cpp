

#include <vector>
#include "k_means.h"


using namespace std;

typedef struct _VECT_{
	float x;
	float y;
	float z;
}VECT;




int main (int argc, char const *argv[])
{
	VECT v1={0};
	v1.x=1.0;
	v1.y=2.0;
	v1.z=3.0;
	VECT v2={0};
	v1.x=3.0;
	v1.y=4.0;
	v1.z=5.0;
	
	vector<VECT> a;
	vector<VECT> b;
	a.push_back(v1);
	a.push_back(v2);
	v2.x=7;
	a.push_back(v2);
	v2.x=19;
	a.push_back(v2);
	v2.x=8;
	a.push_back(v2);
	
	
	KMeans<VECT,float> kmeans(10,3);
	kmeans.setData(a);
	kmeans.Cluster();
	//Mykmean<int> mykeanms();
	//mykeanms.setData(a);
	//kmeans.comper(v1,v2);
	

	return 0;
}