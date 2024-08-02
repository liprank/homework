#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

class Point{
public:
	Point(int x,int y)
	:_ix(x)
	,_iy(y)
	{}

	void print(){
		cout << "(" << _ix << "," << _iy << ")" << endl;
	}

private:
	int _ix;
	int _iy;
};

int main(){
	vector<unique_ptr<Point>> v1;
	v1.push_back(unique_ptr<Point>(new Point(1,3)));
	v1.push_back(unique_ptr<Point>(new Point(2,4)));
	v1.push_back(unique_ptr<Point>(new Point(3,4)));
	v1.push_back(unique_ptr<Point>(new Point(4,5)));

	for(auto &ch : v1){
		ch.get()->print();
	}
	
}
