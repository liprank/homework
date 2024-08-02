#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

class point{
public:
	static point &getInitance(){
		if(nullptr == _initance){
			_initance = new point(1,2);
		}
		return *_initance;
	}

	void init(int x, int y){
		_ix = x;
		_iy = y;
	}


	void print() const{
		cout << "("	<< this->_ix
		<< "," << this->_iy << ")" << endl;
	}

	~point(){
		cout << "~point()" << endl;
	}

	//禁止复制和赋值操作
	point(const point&) = delete;
	point& operator=(const point&) = delete;

private:
	point(int x, int y)
	:_ix(x)
	,_iy(y)
	{
		cout << "point(int,int)" << endl;
	}

private:
	int _ix;
	int _iy;
	static point* _initance;
};
point* point::_initance = nullptr;



int main(){
	vector<point*> array;
	point& elem = point::getInitance();
	//复制函数被删除，只能使用引用操作元元素
	array.push_back(&elem);	

	//point& elem1 = point::getInitance();
	//elem1.init(1,3);
	//array.push_back(&elem1);

	//point& elem2 = point::getInitance();
	//elem1.init(1,4);
	//array.push_back(&elem2);

	//point& elem3 = point::getInitance();
	//elem1.init(1,5);
	//array.push_back(&elem3);

	//point& elem4 = point::getInitance();
	//elem1.init(1,6);
	//array.push_back(&elem4);

	for(auto * elem : array){
		elem->print();
	}

	return 0;
}


