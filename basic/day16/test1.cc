#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int gNum = 10;
int && func1(){
	return std::move(gNum);
}

void test1(){
	&func1();	
	int && ref = func1();
	&ref;
}

string func2(){
	string str1("wangdao");
	return str1;
}

void test2(){
	func2();
	&func2();
	string && ref = func2();
	&ref;
}



