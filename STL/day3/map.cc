#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::string;

void test(){
	map<int,string> m = {{1,"beijing"},{2,"shanghai"}};
	m.insert({3,"beijing"});
	m.insert({1,"wuhan"});
	for(auto elem : m){
		cout << elem.second << endl;
	}

}

void test1(){
	multimap<int,string> m = {{1,"beijing"},{2,"shanghai"}};
	m.insert({3,"beijing"});
	m.insert({1,"wuhan"});
	for(auto elem : m){
		cout << elem.first << elem.second << endl;
	}

}
int main(){
	test1();
	return 0;
}
