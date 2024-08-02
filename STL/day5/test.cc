#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

bool func(int value){
	return value > 5;
}

void test(){
	vector v1 = {1,2,3,4,5,6,7,8,9};	
	for_each(v1.begin(),v1.end(),[](int &value){
			cout << value << " ";
			});
	cout << endl;

	auto it = remove_if(v1.begin(),v1.end(),func);
	v1.erase(it,v1.end());
	for_each(v1.begin(),v1.end(),[](int &value){
			cout << value << " ";
			});
	cout << endl;
}

void test1(){
	vector v1 = {1,2,3,4,5,6,7,8,9};	
	for_each(v1.begin(),v1.end(),[](int &value){
			cout << value << " " ;
			});
	cout << endl;


}

int main(){
	test();
	return 0;
}


