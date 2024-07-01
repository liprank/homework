#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class point{
public:
	//返回类型设为引用，避免复制
	static point & getInstance(){
		static point pt(1,2);
		return pt;
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

private:
	int _ix;
	int _iy;
};

void test0(){
	point &pt = point::getInstance();
	pt.print();

}

int main(){
	test0();
	return 0;
}


