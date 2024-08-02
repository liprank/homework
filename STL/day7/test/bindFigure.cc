#include <math.h>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::function;
using std::bind;

class Rectangle
{
public:
    Rectangle(double length = 0, double width = 0)
    : _length(length)
    , _width(width)
    {
        cout << "Rectangle(double = 0, double = 0)" << endl;
    }

    void display(int x) const 
    {
        cout << "Rectangle";
    }

    double area() const 
    {
        return _length * _width;
    }

    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }
private:
    double _length;
    double _width;
};

class Circle
{
public:
    Circle(double radius = 0)
    : _radius(radius)
    {
        cout << "Circle:" << radius << endl;
    }

    void print() const 
    {
        cout << "Circle" << endl;
    }

    double printArea() const 
    {
		cout << 3.14 * _radius *_radius << endl;
        return 3.14 * _radius *_radius;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }

private:
    double _radius;
};

class Triangle
{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0, double = 0, double = 0)" << endl;
    }

    void show() const 
    {
        cout << "Triangle";
    }

    double showArea() const 
    {
        //海伦公式
        double tmp = (_a + _b + _c)/2;

        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

    ~Triangle()
    {
        cout << "~Triangle()" << endl;
    }
private:
    double _a;
    double _b;
    double _c;
};

class Figure{
public:
	using PcallBack = function<void()>;
	using AcallBack = function<double()>;

	PcallBack _P;
	AcallBack _A;

	void setPcallBack(PcallBack && cb){
		_P = std::move(cb);
	}

	void setAcallBack(AcallBack && cb){
		_A = std::move(cb);
	}

	void handlePcallBack(){
		if(_P){
			_P();
		}
	}

	double handleAcallBack(){
		if(_A){
			return _A();
		}else{
			return 0.0;
		}
	}
};

void Func(Figure &fig){
	fig.handlePcallBack();
	fig.handleAcallBack();
}

void test(){
    Rectangle rectangle(10, 20);
    Circle circle(10);
    Triangle triangle(3, 4, 5);
	cout << endl;

	Figure fig;
	fig.setPcallBack(bind(&Circle::print,&circle));
	fig.setAcallBack(bind(&Circle::printArea,&circle));
	Func(fig);
}

int main(){
	test();
	return 0;
}
