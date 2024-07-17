#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

template <typename Container>
void display(const Container &con){
	for(auto &elem : con){
		cout << elem << " ";
	}

	cout << endl;
}

void test(){
	list<int> number = {1,3,4,7,5,5,3,5,5,3,8};
	number.sort();	
	number.unique();
	display(number);

	list<int> other = {11,22,33,44,2};
	other.sort();
	number.merge(other);
	display(number);
}

void test1(){
	list<int> number = {1,3,4,9};
	list<int> other = {11,22,33,44,5};

	auto it = number.begin();
	++it;
	++it;
	auto it3 = number.begin();
	--it3;
	auto it1 = other.end();
	++it1;
	auto it2 = other.end();
	number.splice(it,other,it3);
	display(number);
}

int main(){
	test1();
	return 0;
}
