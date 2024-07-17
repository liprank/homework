#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::vector;

template<typename T,typename Compare=std::less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare com);
    void quick(int left, int right, Compare &com);
    int partition(int left, int right, Compare &com);
    void print();
private:
    vector<T> _vec;
};

template<typename T,typename Compare>
MyQsort<T,Compare>::MyQsort(T *arr, size_t size, Compare com){
	for(int i = 0;i < size;i++){
		_vec.push_back(arr[i]);
	}
	//quick(0,size - 1,com);
}

template<typename T,typename Compare>
void MyQsort<T,Compare>::print(){
	/* auto it = _vec.begin(); */
	/* for(;it != _vec.end();++it){ */
	/* 	cout << *it << " "; */
	/* } */

	for(auto elem : _vec){
		cout << elem << " ";
	}

	cout << endl;
}

template<typename T,typename Compare>
int MyQsort<T,Compare>::partition(int left, int right, Compare &com){
	T pivot = _vec[left];
	int i = left;
	int j = right;
	while(i < j){
		while(_vec[i] < pivot) ++i;
		while(_vec[j] > pivot) --j;
		if(i < j){
			T temp = _vec[i];
			_vec[i] = _vec[j];
			_vec[j] = temp;
		}
	}
	_vec[left] = _vec[i];	
	_vec[i] = pivot;
	return i;
}

template<typename T,typename Compare>
void MyQsort<T,Compare>::quick(int left, int right, Compare &com){
	if(left >= right) return;
	int mid = partition(left,right,com);	
	quick(left, mid-1, com);
	quick(mid+1, right, com);
}


int main(){
	int arr[5] = {4,5,3,2,1};
	MyQsort q1(arr,5);
	q1.quick(0,4);
	q1.print();
}
