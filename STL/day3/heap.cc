#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size);
    void heapAdjust(size_t ,size_t);
    void sort();
    void print();
private:
    vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
HeapSort<T,Compare>::HeapSort(T *arr, size_t size){
	for(int i = 0; i < size; ++i){
		_vec.push_back(arr[i]);
	}

	sort();
	print();

	int len = size;
	while(len > 1){
		T temp = _vec[0];
		_vec[0] = _vec[len -1];
		_vec[len - 1] = temp; 

		len--;
		heapAdjust(0,len);
		print();
	}
}

template <typename T, typename Compare>
void HeapSort<T,Compare>::print(){
	for(auto elem : _vec){
		cout << elem << " ";
	}
	cout << endl;
}

template <typename T, typename Compare>
void HeapSort<T,Compare>::heapAdjust(size_t i, size_t n){
	while(i < n){
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t maxIdex = i;	

		if(left < n && _vec[left] > _vec[maxIdex]){
			maxIdex = left;
		}

		if(right < n && _vec[right] > _vec[maxIdex]){
			maxIdex = right;
		}

		if(maxIdex == i) break;
		T temp = _vec[i];
		_vec[i] = _vec[maxIdex];
		_vec[maxIdex] = temp; 
		i = maxIdex;
	}
}

template <typename T, typename Compare>
void HeapSort<T,Compare>::sort(){
	int n = _vec.size();
	int i = n / 2 - 1;	
	for(; i >= 0; --i){
		heapAdjust(i,n);
	}
}

void test(){
	int arr[10] = {11,4,55,6,33,2,10,7,9,1};
	HeapSort<int> h1(arr,10);
	//h1.sort();
}

int main(){
	test();
	return 0;
}

