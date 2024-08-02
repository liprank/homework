#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
	Base(int x)
	:_value(x)
	{}

	friend
	int operator+(const Base& x,const Base& y){
		Base z(y._value - x._value);
		return z._value;
	}

private:
	int _value;
};

int main(){
	int i =2;
	int j=7;
	
	Base x(i);
	Base y(j);
	cout << (x+y == j - i) << endl;
}
