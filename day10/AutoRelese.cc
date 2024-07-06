#include <iostream>

using std::cout;
using std::endl;


class Singleton{
public:
	static Singleton* getInstance(){
		if(nullptr == pInstance){
			pInstance = new Singleton(1,2);
		}
		return pInstance;
	}
	
	void init(int x,int y){
        _ix = x;
        _iy = y;
    }

	//静态函数能调用静态成员函数
	static void destroy(){
		if(pInstance){
			delete pInstance;
			pInstance = nullptr;
			cout << ">>>delete heap<<<" << endl;
		}
	}

    void print() const{
             cout << "(" << this->_ix
            << "," << this->_iy
            << ")" << endl;
    }

	//设置为友元类
	friend class AutoRelese;
private:
	Singleton(const Singleton & rhs) = delete;
	Singleton & operator=(const Singleton& rhs) = delete;

	Singleton(int x,int y)
	:_ix(x)
	,_iy(y)
	{
		cout << "Singleton(x,y)" << endl;
	}

	~Singleton(){
		cout << "~Singleton()" << endl;	
	}

private:
	int _ix;
	int _iy;
	static Singleton* pInstance;
};
Singleton* pInstance = nullptr;

class AutoRelese{
public:
	AutoRelese(Singleton* p)
	:_p(p)
	{}

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
    AutoRelese ar(Singleton::getInstance());
    Singleton::getInstance()->init(7,8);
    Singleton::getInstance()->print();
    /* Singleton::destroy(); */


    /* AutoRelease ar2(Singleton::getInstance()); */
}


int main(void){
    test0();
    return 0;
}
