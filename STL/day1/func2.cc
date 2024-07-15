#include <iostream>
#include <map>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))
using std::cout;
using std::endl;
using std::map;



int main(){
	int arr[9] = {1,2,3,2,2,2,5,4,2};
	map<int,int>m1;
	for(int i : arr){
		m1[i]++;	
	}
	
	for(auto elem : m1){
		if(elem.second > SIZE(arr)/2){
			cout << elem.first << endl; 
		}
	}
}
