#include <iostream>

using std::cout;
using std::endl;

template <class T,class... Args>
T sum(T x,Args... args){
	return x + sum<Args...>(args...); 	
}

template <class T>
T sum(){
	return 0;
}

void test0(){
	cout << sum(1,3,4,5,6) << endl;
	cout << sum(1,3.9,4.7,5.8,6) << endl;
}

int main(){
	test0();
	return 0;
}
