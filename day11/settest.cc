#include <iostream>
#include <map>
#include <set>
#include <string.h>

using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;

void test0(){
	set<int> nums;
	set<int> nums2 = {1,3,5,6,8,1,3,5};
	set<int> nums3 = nums2;
	set<int> nums4(nums2.begin(),nums2.end());

	for(auto n : nums4){
		cout << n << " "; 
	}
	cout << endl;

	auto it = nums3.begin();
	for(;it!=nums3.end();++it){
		cout << *it << " ";
	}
	cout << endl;

	cout << nums2.count(3) << endl;
	cout << nums2.count(2) << endl;

	set<int>::iterator it2 = nums3.find(8);
	if(it2 == nums3.end()){
		cout << "it is not exist" << endl;
	}else{
		cout << *it2 << endl;
	}

	int number[4] = {0,9,8,7};
	nums4.insert(number,number+4);
	for(auto n : nums4){
		cout << n << " "; 
	}
	
	cout << endl;
}

int main(){
	test0();

	return 0;
}
