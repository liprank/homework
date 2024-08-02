#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

template <class T>
T add(T x,T y){
	return x+y;
}

template <>
set<int> add<set<int>>(const set<int>s1,const set<int>s2){
	set<int> result;
	for(auto ch : s1){
		result.insert(ch);	
	}

	for(auto ch : s2){
		result.insert(ch);	
	}

	return result;
}

void test0(){
	cout << add(1,3) << endl;
	cout << add(1.2,3.4) << endl;
	
	set<int> s1 = {1,2};
	set<int> s2 = {3,4};
	set<int> result = add(s1,s2); 
	for(auto ch : result){
		cout << ch << " ";
	}
	cout << endl;
}

int main(){
	test0();
	return 0;
}

