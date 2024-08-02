#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class point{
public:
	static point * getInstance(){
		if(_pInstance == nullptr){
			_pInstance = new point(1,2);
		}
		return _pInstance;
	}

	void init(int x, int y){
		_ix = x;
		_iy = y;
	}

	//销毁静态成员，用静态函数销毁可直接访问
	//可控制销毁顺序
	static void destroy(){
		if(_pInstance){
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	void print() const{
		cout << "("	<< this->_ix
		<< "," << this->_iy << ")" << endl;
	}


private:
	point(int x, int y)
	:_ix(x)
	,_iy(y)
	{
		cout << "point(int,int)" << endl;
	}

	~point(){
		cout << "~point()" << endl;
	}

	//删除拷贝复制、赋值运算符重载
	point(point & rhs) = delete;
	point & operator=(const point & rhs) = delete;

private:
	int _ix;
	int _iy;
	//定义一个指针指向第一次创建的对象
	static point* _pInstance;
};
//静态变量初始化
point* point::_pInstance = nullptr;

void test0(){
	point::getInstance()->print();
	point::getInstance()->init(7,8);
	point::getInstance()->print();
	point::destroy();
}

int main(){
	test0();
	return 0;
}


