#include <iostream>

using std::cout;
using std::endl;

class Singleton{
public:
	static Singleton* getInstance(){
		if(nullptr == _pInstance){
			_pInstance = new Singleton(1,1);
		}
		return _pInstance;
	}

	void init(int x,int y){
		this->_ix = x;
		this->_iy = y;
	}

	void print() const{
		cout << "(" << this->_ix << "," << this->_iy << ")" << endl;
	}

private:
	Singleton & operator=(const Singleton & rhs) = delete;
	Singleton(const Singleton & rhs) = delete;

	Singleton(int x,int y)
	:_ix(x)
	,_iy(y)
	{
		cout << "Singleton()" << endl;
	}

	~Singleton(){
		cout << "~Singleton()" << endl;
	}

	friend class AutoRelese;
private:
	int _ix;
	int _iy;
	static Singleton* _pInstance;
};
Singleton* Singleton::_pInstance = nullptr;

class AutoRelese{
public:
	AutoRelese(Singleton* p)
	:_p(p)
	{
		cout << "AutoRelese()" << endl;	
	}

	~AutoRelese(){
		if(_p){
			delete _p;
			_p = nullptr;	
			cout << "~AutoRelese()" << endl;
		}
	}
private:
	Singleton* _p;
};

void test0(){
	AutoRelese a(Singleton::getInstance());
	Singleton::getInstance()->init(3,4);
	Singleton::getInstance()->print();
}

int main(){
	test0();
	return 0;
}
