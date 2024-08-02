#include "Line.hh"
#include <iostream>

using std::cout;
using std::endl;

class Line::LineImp1{
	class Point{
	public:
		Point(int x,int y)
		:_ix(x)
		,_iy(y)
		{}

		~Point(){
			cout << "~Point()" << endl;
		}

		void print() const{
			cout << "(" << _ix << "," << _iy << ")" << endl;
		}
	private:
		int _ix;
		int _iy;
	};

public:
	LineImp1(int x1,int y1,int x2,int y2)
	:_pt1(x1,y1)
	,_pt2(x2,y2)
	{
		cout << "iLineImp1(int*4)" << endl;
	}

	~LineImp1(){
		cout << "~LineImp1" << endl;
	}

	void printLine() const{
		_pt1.print();
		cout << "--->";
		_pt2.print();
		cout << endl;
	}
private:
	Point _pt1;
	Point _pt2;
};

Line::Line(int x1,int y1,int x2,int y2)
:_pImp1(new LineImp1(x1,y1,x2,y2))
{
	cout << "Line(int*4)" << endl;
}

Line::~Line(){
	cout << "~Line()" << endl;
}

void Line::printLine() const{
	_pImp1->printLine();
}
