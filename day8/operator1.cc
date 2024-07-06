#include <iostream>
using std::cout;
using std::endl;


class Complex{
public:
	Complex(int x,int y)
	:_ix(x)
	,_iy(y)
	{}

	void print(){
		cout << _ix << "+" << _iy << "i" << endl;
	}

	//1.设置友元
	//friend
	//Complex add(Complex &x,Complex &y){
	//	Complex z(x._ix+y._ix,x._iy+y._iy);
	//	return z;
	//}

	//2.运算符重载,成员函数
	Complex operator+(Complex &x){
		Complex z(x._ix+this->_ix,x._iy+this->_iy);
		return z;
	}

	int getx(){
		return this->_ix;
	}

	int gety(){
		return this->_iy;
	}
private:
	int _ix;
	int _iy;
};


//Complex operator+(Complex &x,Complex &y){
//	Complex z(x.getx()+y.getx(),x.gety()+y.gety());
//	return z;
//}

int main(){
	Complex p1(3,4);
	Complex p2(4,5);
	p1.print();
	//Complex p3 = add(p1,p2);
	//p3.print();

	Complex p4 = p1 + p2;
	p4.print();
}
