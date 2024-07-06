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

	//1.+=运算符重载,倾向于使用成员函数
	Complex & operator+=(Complex &x){
		cout << "execute += operator" << endl;
		_ix += x._ix;
		_iy += x._iy;
		return *this;
	}

private:
	int _ix;
	int _iy;
};

int main(){
	Complex p1(3,4);
	Complex p2(4,5);
	p1.print();

	p1 += p2;
	p1.print();
}
