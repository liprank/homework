#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Computer{
public:
	Computer(const char* brand,double price)
	:_brand(new char[strlen(brand)+1])
	,_price(price)
	{
		_totalPrice += price;
		cout << "Computer" << endl;
		strcpy(_brand,brand);
	}

	~Computer(){
		cout << "~Computer" << endl;
		if(_brand){
			_totalPrice -= _price;
			delete [] _brand;
			_brand = nullptr;
		}
	}

	Computer(const Computer & rhs)
	:_brand(new char(strlen(rhs._brand) + 1))
	,_price(rhs._price)
	{
		_totalPrice += _price;
		cout << "Computer" << endl;
		strcpy(_brand,rhs._brand);
	}	

	Computer & operator=(const Computer & rhs){
		cout << "equal function" << endl;
		if(this != &rhs){
			_totalPrice -= _price;
			delete [] _brand;
			_brand = new char[strlen(rhs._brand) + 1]();
			strcpy(_brand,rhs._brand);
			_price = rhs._price;
			_totalPrice += _price;
		}
		return *this;
	}

	void print() const{
		_brand[0] = 'x';
		cout << "brand:" << _brand << endl;
		cout << "price:" << _price << endl;
	}

	static void printTotalPrice(){
		cout << "TotalPrice:" << _totalPrice << endl;
	}

private:
	char* _brand;
	double _price;
	static double _totalPrice;
};

double Computer::_totalPrice = 0;

void test0(){
	Computer::printTotalPrice();
	cout << sizeof(Computer) << endl;
	Computer pc("Apple",20000);
	Computer pc2("Huawei",21000);
	Computer pc3("Acer",8000);
	pc3.print();

	Computer::printTotalPrice();
}

int main(){
	test0();
	return 0;
}





