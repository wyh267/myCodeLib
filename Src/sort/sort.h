

#ifndef _SORT_H_
#define _SORT_H_


#include <iostream>
#include <vector>


using namespace std;

namespace aglo{

	template<typename T>
	class SortClass{
	public:
		SortClass(vector<T>& sort_list,bool(*comp)(T,T),void(*_swap)(T&,T&)){
			m_sort_list=&sort_list;
			compre=comp;
			swap=_swap;
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
						
						swap((*m_sort_list)[i],(*m_sort_list)[j]);
						
					}

				}

			}
			
		}
		
	
		//
		//	快速排序
		//
		void quickSort(){
			_quickSort((*m_sort_list),0,(*m_sort_list).size()-1);
		}
		
		
		//
		//	选择排序
		//
		void selectionSort(){
			
			int min_index;

			for(size_t i = 0; i < (*m_sort_list).size()-1; ++i)
			{
				min_index=i;
				for(size_t j = i+1; j < (*m_sort_list).size(); ++j)
				{
					if ( compre((*m_sort_list)[min_index],(*m_sort_list)[j]) == true)
						min_index=j;
					
				}
				
				if (i != min_index)
				{
					swap((*m_sort_list)[min_index],(*m_sort_list)[i]);
					
				}
			}
			
		}
		
		
		//
		//	归并排序
		//
		void mergeSort(){
			vector<T> merge;
			_mergeSort((*m_sort_list),merge,0,(*m_sort_list).size());
		}
		
		
		//
		//	堆排序
		//
		void heapSort(){
	
			buildHeap();
			for(int i = (*m_sort_list).size()-1; i > 0; --i)
			{
				swap((*m_sort_list)[0],(*m_sort_list)[i]);
								
				adjHeap(0,i);

			}
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
		void (*swap)(T&,T&);
		
		//
		//
		//
		void _mergeSort(vector<T>source,vector<T>target,int start,int end){
			
			
			
			
		}
		
		//
		//	堆排序，调整堆
		//
		void adjHeap(int start,int size){
			
			
	
			int left=start*2+1;
			int right=start*2+2;
	
			
			if(  ( compre((*m_sort_list)[start],(*m_sort_list)[left]) == false )  &&left < size){
				
				swap((*m_sort_list)[start],(*m_sort_list)[left]);
				
			
				adjHeap(left,size);
			}
			
			if(  ( compre((*m_sort_list)[start],(*m_sort_list)[right]) == false ) && right < size){
				swap((*m_sort_list)[start],(*m_sort_list)[right]);
				
				
				adjHeap(right,size);
			}	
			
				
			return ;
			
			
		}
		
		//
		//	堆排序，建立堆
		//
		void buildHeap(){
			
			for(int i = ((*m_sort_list).size()-1)/2; i >= 0 ; --i)
			{
				adjHeap(i,(*m_sort_list).size());
			}
			
			
		}
		
		
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
					swap(arr[i],arr[j]);
				               
					
				}
				   
				   
				while(i<j&&compre(arr[j],arr[i])){    
					i++;
				}
				if(i<j){   
					swap(arr[i],arr[j]);              
					
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



void swap(int &a,int &b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
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
	makeArray(a,10);
	aglo::SortClass<int> sort(a,comp,swap);
	
	cout << "############### 快速排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.quickSort();
	cout << "排序后::: ";
	sort.displaySort();
	cout << endl;
	
	
	a.clear();
	makeArray(a,10);
	cout << "############### 插入排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.insertSort();
	cout << "排序后::: ";
	sort.displaySort();
	cout << endl;
	a.clear();
	makeArray(a,10);
	cout << "############### 冒泡排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.bubbleSort();
	cout << "排序后::: ";
	sort.displaySort();
	cout << endl;
	a.clear();
	makeArray(a,10);
	cout << "############### 选择排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.selectionSort();
	cout << "排序后::: ";
	sort.displaySort();
	cout << endl;
	a.clear();
	makeArray(a,10);
	cout << "############### 堆排序法 ###############" << endl;
	cout << "排序前::: " ;
	sort.displaySort();
	sort.heapSort();
	cout << "排序后::: ";
	sort.displaySort();
	
	
	
	
	
	
	return 0;
}

#endif