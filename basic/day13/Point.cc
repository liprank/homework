#include <iostream>
#include <string.h>
#include <math.h>

using std::cout;
using std::endl;
using std::string;

class Point{
public:
	Point(float a,float b)
	:_ix(a)
	,_iy(b)
	{}

	Point(const Point& rhs){
		_ix = rhs._ix;
		_iy = rhs._iy;

	}

	float _ix;
	float _iy;
};

class Color{
public:
	Color(const string s1){
		_color = s1;
	}

	Color(const Color& rhs){
		_color = rhs._color;
	}

	string _color;
};

class Line{
public:
	Line(const Line& rhs)
	:_start(rhs._start)
	,_end(rhs._end)
	{}

	Line(const Point& p1,const Point& p2)
	:_start(p1)
	,_end(p2)
	{}

	double length(){
		int a = abs(_start._ix - _end._ix);
		int b = abs(_start._iy - _end._iy);
		return pow(a*a+b*b,0.5);
	}

	Point _start;
	Point _end;
};

class Triangle
:public Line
,public Color
{
public:
	Triangle(Color c,Line l,int height)
	:Line(l)
	,Color(c)
	,_height(height)
	{}

	float _height;

	void area(){
		cout << length() * _height * 0.5 << endl;
	}

	void circumference(){
		int a = length();
		cout << pow(a*a+_height*_height,0.5) << endl;
	}

	void color(){
		cout << _color << endl;
	}
};

void test0(){
	Color c1("red");	
	Point p1(3,4);
	Point p2(0,0);
	Line l1(p1,p2);

	Triangle t1(c1,l1,6);
	cout << t1._height << endl;

	t1.area();
	t1.color();

}

int main(){
	test0();
	return 0;
}
