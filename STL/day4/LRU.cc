#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::list;
using std::unordered_map;
using std::pair;

class LRUCache{
public:
	typedef list<pair<int,int>>::iterator lPairIt;
	LRUCache(int capacity)
	: _capacity(capacity)
	{}

	int get(int key);
	void put(int key,int value);
	lPairIt findkey(int key);

	void display()const;
private:
	int _capacity;
	int _used=0;
	list<pair<int,int>> l1;
};

void LRUCache::display()const{
	auto it = l1.begin();
	cout << "缓存是{";
	cout << it->first << "=" << it->second;

	++it;	
	for(;it != l1.end(); ++it){
		cout <<"," << it->first << "=" << it->second;
	}
	cout << "}" << endl;
}

LRUCache::lPairIt LRUCache::findkey(int key){
	auto it = l1.begin();
	for(;it != l1.end(); ++it){
		if(it->first == key){
			return it;
		}
	}
	return l1.end();
}

void LRUCache::put(int key,int value){
	if(_used < _capacity){
		auto it = findkey(key); 
		if(it == l1.end()){
			l1.push_back({key,value});
		}else{
			it->second = value;
			l1.splice(l1.end(),l1,it);//将it所指向的位置移动到末尾
		}
		++_used;
		display();
	}else if(_used == _capacity){
		auto toDeleteIt = l1.begin();	
		cout << "该操作会使得关键字" << toDeleteIt->first << "作废" 
			 << ",";

		l1.erase(toDeleteIt);//删除第一个元素
		l1.push_back({key,value});

		display();
	}
}

int LRUCache::get(int key){
	auto it = findkey(key);
	if(it == l1.end()){
		cout << -1 << "未找到" << endl;
		return -1;
	}else{
		cout << it->first << endl;
		l1.splice(l1.end(),l1,it);//将it所指向的位置移动到末尾
		return it->first;
	}
}

void test(){
	LRUCache lRUCache(2);
	lRUCache.put(1, 1); // 缓存是 {1=1}
	lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
	lRUCache.get(1); // 返回 1
	lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
	lRUCache.get(2); // 返回 -1 (未找到)
	lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
	lRUCache.get(1); // 返回 -1 (未找到)
	lRUCache.get(3); // 返回 3
	lRUCache.get(4); // 返回 4
}

int main(){
	test();
	return 0;
}
