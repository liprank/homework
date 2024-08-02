#include <iostream>
#include <string.h>
#include <math.h>

using std::cout;
using std::endl;
using std::string;

class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是:" 
         << fig.getArea() << endl ;
}

class Rectangle
:public Figure
{
public:
Rectangle(int x,int y)
:_ix(x)
,_iy(y)
{
	_name = "Rectangle";
}

string getName() const override{
	return _name;
}

double getArea() const override{
	return _ix * _iy; 
}

private:
	string _name;
	int _ix;
	int _iy;
};

class Circle
:public Figure
{
public:
Circle(int x)
:_r(x)
{
	_name = "Circle";
}

string getName() const override{
	return _name;
}

double getArea() const override{
	return  4 / 3 * 3.14 * pow(_r,3);
}

private:
	string _name;
	int _r;
};

class Triangle
:public Figure
{
public:
Triangle(int x,int y,int z)
:_ix(x)
,_iy(y)
,_iz(z)
{
	_name = "Triangle";
}

string getName() const override{
	return _name;
}

double getArea() const override{
	double s = (_ix+_iy+_iz)/2;
	return pow(s*(s-_ix)*(s-_iy)*(s-_iz),0.5);
}

private:
	string _name;
	int _ix;
	int _iy;
	int _iz;
};

void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}

int main(){
	test();
	return 0;
}
