#include <iostream>
using std::endl;
using std::cout;

class Point{
public:
	Point(int x, int y)
	:_ix(x)
	,_iy(y)
	{
		cout<< "Point(int,int)" << endl;
	}	

	Point(const Point & rhs)
	:_ix(rhs._ix)
	,_iy(rhs._iy)
	{
		cout << "Point(int,int)" << endl;	
	}

	~Point(){
		cout << "~Point" << endl;
	}

	void print() const{
		cout << "const print" << endl;
		cout << "(" << _ix << "," << _iy << ")" << endl;
	}

private:
	int _ix;
	int _iy;
};

void test0(){
	const int a = 1;
	Point pt(10,8);
	Point pt2(pt);
	pt2.print();
}

int main(){
	test0();
	return 0;
}
