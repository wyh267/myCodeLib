#ifndef _K_MEANS_H_
#define _K_MEANS_H_

#include <vector>
#include <iostream>
#include <math.h>
#include <map>

using namespace std;


template <typename VEC,typename DIS> //value type
class KMeans{
	
	enum InitMode{
		kCustom,
		kAuto
	};
	
	
public:
	KMeans(int vec_size=10,int k=3){
		m_vec_size=vec_size;
		m_k=k;
	}
	
	~KMeans(){
		
		
	}
	
	
	bool setMode(InitMode mode){
		
		m_mode=mode;
		
	}
	
	void setData(vector<VEC> data){
		
		typename vector<VEC>::iterator it;
		m_data=data;
		for(size_t i = 0; i < m_k; ++i)
		{
			m_center.push_back(m_data[i]);
			
			/* code */
		}
		for(it=m_center.begin();it!=m_center.end();it++)
				cout <<" Rand: " <<  it->x << " ";
		
		cout<<endl;
		
	}
	
	
	void Cluster(){
		
		typename vector<VEC>::iterator itc;
		typename vector<VEC>::iterator it;
		typename map<VEC, vector<VEC>* >::iterator itm;
		vector<VEC> a;
		for(itc=m_center.begin();itc!=m_center.end();itc++)
		{
			cluster_map[*itc]=a;
		}
		
		for(it=m_data.begin();it!=m_data.end();it++){
			vector<DIS> distances;
			//cluster_map[m_data[i]]=
			DIS last_distance=999999;
			cluster_map[m_center[0]].push_back(*it);
			for(size_t i = 0; i < m_center.size(); ++i)
			{
				DIS distance=calcDistance(*it,m_center[i]);
				if(last_distance > distance){
					cluster_map[m_center[i-1]].pop_back();
					cluster_map[m_center[i]].push_back(*it);
				}
				
			}
				
		}
		
		for(itm=cluster_map.begin();itm!=cluster_map.end();itm++)
		{
			//for(it=(*itm).begin();it!=(*itm).end();it++)
			//{
				//cout << "X:" << it->x;
				//}
			cout << endl;
		}
			
		
		
		
		
	}
	
	
	
	
	DIS calcDistance(VEC v1,VEC v2){
		DIS distance;
		
		distance= sqrt((v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y) + (v1.z-v2.z)*(v1.z-v2.z));
		
		return distance;
		
	}
	
	
	DIS minDistance(DIS d1,DIS d2){
		
		return d1<=d2?d1:d2;
	}
	
	
	
	void comper(VEC v1,VEC v2){
		typename vector<VEC>::iterator it;
		for(it=m_data.begin();it!=m_data.end();it++)
				cout << it->x << endl;
		//cout << m_data.x << "   " << m_data.x << endl;
	}
	


private:
	int m_vec_size;
	int m_k;
	InitMode m_mode;
	vector<VEC> m_data;
	vector<VEC> m_center;
	std::map<VEC, vector<VEC> > cluster_map;
};















#endif




