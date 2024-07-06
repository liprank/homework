#include <iostream>

using std::cout;
using std::endl;

class Singleton{
	class AutoRelese{
	public:
		AutoRelese()
		{
			cout << "AutoRelese()" << endl;	
		}
	
		~AutoRelese(){
			if(_pInstance){
				delete _pInstance;
				_pInstance = nullptr;	
				cout << "~AutoRelese()" << endl;
			}
		}
	};

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
	static AutoRelese _ar;
};
Singleton* Singleton::_pInstance = nullptr;
Singleton::AutoRelese Singleton::_ar;


void test0(){
	Singleton::getInstance()->init(5,6);
	Singleton::getInstance()->print();
}

int main(){
	test0();
	return 0;
}
