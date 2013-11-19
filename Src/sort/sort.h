

#ifndef _SORT_H_
#define _SORT_H_


#include <iostream>
#include <vector>


using namespace std;

namespace aglo{

	template<typename T>
	class SortClass{
	public:
		SortClass(vector<T>& sort_list,bool(*comp)(T,T)){
			m_sort_list=&sort_list;
			compre=comp;
		}
	
	
		~SortClass(){
			
		}
		
		//
		//	插入排序法
		//
		void insertSort(){
			int j;
			T temp;
			for(size_t i = 1; i < (*m_sort_list).size(); ++i)
			{
				temp=(*m_sort_list)[i];
				j=i-1;
				while((j>=0) && (compre((*m_sort_list)[j],temp)==true)){
					(*m_sort_list)[j+1] = (*m_sort_list)[j];
					j--;
				}
				(*m_sort_list)[j+1] = temp;
				/* code */
			}
			
		}
		
		
		//
		//	冒泡排序法
		//
		void bubbleSort(){
			
			for(size_t i = 0; i < (*m_sort_list).size(); ++i)
			{
				for(size_t j = i+1; j < (*m_sort_list).size(); ++j)
				{
					if(compre((*m_sort_list)[i],(*m_sort_list)[j])==true){
						T tmp;
						tmp=(*m_sort_list)[j];
						(*m_sort_list)[j]=(*m_sort_list)[i];
						(*m_sort_list)[i]=tmp;
					}
					/* code */
				}
				/* code */
			}
			
		}
		
		
		//
		//	快速排序
		//
		void quickSort(){
			_quickSort((*m_sort_list),0,(*m_sort_list).size());
		}
		
		
		void displaySort(){
			
			for(size_t i = 0; i < (*m_sort_list).size(); ++i)
			{
				cout << (*m_sort_list)[i] << ",";
				/* code */
			}
			cout << endl;
			//cout << compre(4,3) << endl;
		}
	
	
	
	
	private:
		vector<T> *m_sort_list;
		bool (*compre)(T,T);
		
		//
		//	快速排序具体实现
		//
		void _quickSort(vector<T>& arr,int start,int end){
			
			int i,j;
			i = start;
			j = end;
			if((arr.size()==0))
			     return;
			         
			while(i<j){
			      
				while(i<j && compre(arr[j],arr[i])){     
					j--;
				}
				if(i<j){                  
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
				   
				   
				while(i<j&&compre(arr[j],arr[i])){    
					i++;
				}
				if(i<j){                 
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
					
			if(i-start>1){
				_quickSort(arr,start,i-1);
			}
					
			if(end-j>1){
				_quickSort(arr,j+1,end);
			}
		}

	
	};

	

	


}


bool comp(int a,int b){
	if (a>=b)
		return true;
	//cout << a << endl;
	return false;
}



void makeArray(vector<int>& array,int num){
		
	for(size_t i = 0; i < num; ++i)
	{
		array.push_back(rand()%1000);
		/* code */
	}
	
}


int main (int argc, char const *argv[])
{
	vector<int> a;
	//cout << rand()%100 << endl;
	//cout << rand()%100 << endl;
	aglo::SortClass<int> sort(a,comp);
	makeArray(a,50);
	cout << "############### 快速排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.quickSort();
	cout << "排序后::: ";
	sort.displaySort();
	cout << endl;
	a.clear();
	makeArray(a,50);
	cout << "############### 插入排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.insertSort();
	cout << "排序后::: ";
	sort.displaySort();
	cout << endl;
	a.clear();
	makeArray(a,50);
	cout << "############### 冒泡排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.bubbleSort();
	cout << "排序后::: ";
	sort.displaySort();
	
	
	
	
	return 0;
}

#endif