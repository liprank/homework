#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;

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

void test1(){
	function<int()> f1 = bind(add,1,2);
	cout << f1() << endl;

	Example ex;
	function<int()> f2 = bind(&Example::add,&ex,3,4);
	cout << f2() << endl;

	using namespace std::placeholders;
	function<int(int)> f3 = bind(add,5,_1);
	cout << f3(6) << endl;

	function<int(int,int)> f4 = bind(add,_1,_2);
	cout << f4(7,8) << endl;


}

int main(){
	test();
	return 0;
}
