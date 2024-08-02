#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
	Point(int x = 0,int y = 0)
	:_ix(x)
	,_iy(y)
	{
		cout << "Point(int,int)" << endl;
	}

	~Point(){
		cout << "~Point()" << endl;
	}

	Point(const Point & rhs)
	:_ix(rhs._ix)
	,_iy(rhs._iy)
	{
		cout << "Point(const Point &)" << endl;
	}
	
	Point & operator=(const Point & rhs){
		_ix = rhs._ix;
		_iy = rhs._iy;
		return *this;
	}

	void print() const{
		cout << "(" << this->_ix
		<< "," << this->_iy
		<< ")" << endl;
	}

private:
	int _ix;
	int _iy;
};

void test0(){
	Point pt(1,2);
	//Point pt2; do not define the non-argument initation
	Point pt2;
	pt2.print();

	Point* p1 = nullptr;
	Point* p2 = &pt;
	Point* p3 = new Point(3,4);
	delete p3;

	int* p = new int();
	delete p;

	Point* p4 = new Point();
	p4->print();
	(*p4).print();
	delete p4;
}

int main(){
	test0();
	return 0;
}






