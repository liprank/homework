#include <math.h>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::multiset;
using std::vector;
using std::pair;

template <typename Container>
void display(const Container &con){
	for(auto elem : con){
		cout << elem << " ";
	}
	cout << endl;
}

void test(){
	multiset<int> number = {1,2,3,3,4,3,5,7,3,9,8};

	auto it = number.count(3);
	cout << it << endl;

	auto item = number.find(8);
	if(item != number.end()) cout << "item finded" << endl;
	else cout << "not find" << endl;

	auto it1 = number.lower_bound(3);
	auto it2 = number.upper_bound(3);
	cout << *it1 << endl;
	cout << *it2 << endl;

	pair<multiset<int>::iterator,multiset<int>::iterator>
		ret = number.equal_range(3);
	while(ret.first != ret.second){
		cout << *ret.first << " ";
		++ret.first;
	}
	cout << endl;
}

int main(){
	test();
	return 0;
}
