#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

int add(int x,int y){
	cout << "add:" ; 
	return x+y;
}

int multiply(int x,int y){
	cout << "multiply" << endl;
	return x*y;
}

class Example{
public:
	int add(int x,int y){
		cout << "add:"; 
		return x+y;
	}
};

void test(){
	auto f1 = bind(add,1,2);
	cout << f1() << endl;

	Example ex;
	//绑定一个函数地址
	auto f2 = bind(&Example::add,ex,3,4);
	cout << f2() << endl;

	using namespace std::placeholders;
	auto f3 = bind(&Example::add,ex,5,_1);
	cout << f3(6) << endl;
}

int main(){
	test();
	return 0;
}
