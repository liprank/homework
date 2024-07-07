#include <iostream>
#include <map>
#include <string.h>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::make_pair;

int main(){
	map<int,string> city = {
	{1,"nanjing"},
	{2,"shanghai"},
	{3,"nanning"},
	pair<int,string>(6,"wuhan"),
	make_pair(7,"shenzhen")
	};

	for(auto & n : city){
		cout << n.first << " " << n.second << endl;
	}

	map<string,int> dict;
	cout << dict["chengdu"] << endl;
	for(auto & n : dict){
		cout << n.first << " " << n.second << endl;
	}
}
