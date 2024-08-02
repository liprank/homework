#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

void incr(int& i){
	++i;
}

void test(){
	int i = 1;	
	cout << i << endl;

	incr(i);
	cout << i << endl;

	using namespace std::placeholders;
	auto inc = bind(incr,_1);
	cout << i << endl;
	
	/* inc(std::ref(i)); */
	inc(i);
	cout << i << endl;
}

int main(){
	test();
	return 0;
}
