#include <iostream>
#include <pthread.h>

using std::cout;
using std::endl;

class Singleton{
public:
	static Singleton* getInstance(){
		pthread_once(&_once,init_r);
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
	static void init_r(){
		if(nullptr == _pInstance){
			_pInstance = new Singleton(1,1);
			atexit(destroy);
		}
	}

	static void destroy(){
		if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
			cout << "destroy" << endl;
		}
	}

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
	static pthread_once_t _once;
};
Singleton* Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

void test0(){
	Singleton::getInstance()->init(10,4);
	Singleton::getInstance()->print();
}

int main(){
	test0();
	return 0;
}
