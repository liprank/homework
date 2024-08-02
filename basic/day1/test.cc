#include <iostream>
using std::cout;
using std::endl;

namespace test{
	int a = 1;
	int b = 2;
	int c[3] = {1,2,3};
}//end of namespace test

int main(){
	using namespace test;
	cout << a << endl;	

	int* p1 = new int();
	cout << p1 <<endl;
	delete p1;

	int* p2 = new int(4);
	cout << p2 <<endl;
	delete p2;

	int* p3 = new int[10]();
	for(int i = 0; i < 10; i++){
		cout << p3[i] << endl;
	}
	delete[] p3;

	int* p4 = new int[3]{1,2,3};
	for(int i = 0; i < 3; i++){
		cout << p4[i] << endl;
	}
	delete[] p4;

	const char* string = "hello world";
	cout << string << endl;

}
