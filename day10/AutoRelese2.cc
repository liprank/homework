#include <iostream>

using std::cout;
using std::endl;

class Singleton{
public:
	static Singleton* getInstance(){
		if(nullptr == _pInstance){
			atexit(destroy);
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

	static void destroy(){
		if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
			cout << "destroy" << endl;
		}
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

void test0(){
	Singleton::getInstance()->init(7,8);
	Singleton::getInstance()->print();
}


int main(){
	test0();
	return 0;
}
