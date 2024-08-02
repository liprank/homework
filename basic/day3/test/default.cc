#include <iostream>
using std::cout;
using std::endl;

void func(int x = 1, int y = 0)
{
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
}

void test0(){
    //传入的参数优先级高于参数默认值
    func(1,2);

    //缺省调用
    func(100);
    func();
}


void func2(int a,int b,int c = 1);

void test1(){
    func2(2,4,5);
    func2(100,200);
}

void func2(int a,int b,int c){
    cout << a + b + c << endl;
}


int main(void){
    test1();
    return 0;
}
