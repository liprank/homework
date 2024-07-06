#include <iostream>
using std::cout;
using std::endl;


class Complex{
public:
	Complex(int x,int y)
	:_real(x)
	,_image(y)
	{}

	void print() const{
		cout << _real << " + " << _image << "i" << endl;	
	}

	//1.前置++，返回源对象
	Complex & operator++(){
		++_real;
		++_image;
		return *this;
	}

	//2.后置++，返回副本	
	Complex operator++(int){
		//默认拷贝构造
		Complex temp(*this);
		++_real;
		++_image;
		return temp;
	}

private:
	int _real;
	int _image;
};

int main(){
	Complex t1(3,4);
	++t1;
	t1.print();
	Complex t2(t1++);
	t1.print();
	t2.print();

}
