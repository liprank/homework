#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test(){
	vector<int> vec = {1,2,3,4,5,5,5,5,5,9,5,6,5};
	
	auto it = vec.begin();
	for(;it != vec.end();){
		if(5 == *it){
			vec.erase(it);
		}else{
			++it;
		}
	}

	auto it1 = vec.begin();
	for(;it1 != vec.end();++it1){
		cout << *it1 << " ";
	}
	cout << endl;
}

int main(){
	test();
	return 0;
}
