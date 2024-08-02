#include "mylog.hh"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test0(){
	LogWarn("this is a warn msg");
	Mylogger::destroy();
}

int main(){
	test0();
	return 0;
}
