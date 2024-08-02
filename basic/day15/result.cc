#include <iostream>

using std::cout;
using std::endl;

class A{
public:
    virtual void a(){ cout << "A::a()" << endl; } 
    void b(){ cout << "A::b()" << endl; } 
    virtual void c(){ cout << "A::c()" << endl; } 
    void e(){ cout << "A::e()" << endl; }
};

class B{
public:
    virtual void a(){ cout << "B::a()" << endl; } 
    void c(){ cout << "B::c()" << endl; } 
    void d(){ cout << "B::d()" << endl; } 
    virtual void f(){ cout << "B::f()" << endl; }
};

class C
: public A
, public B
{
public:
    virtual void a(){ cout << "C::a()" << endl; } 
    virtual void b(){ cout << "C::b()" << endl; } 
    void c(){ cout << "C::c()" << endl; } 
    void d(){ cout << "C::d()" << endl; } 
};

void test0(){
    C c;
    c.a(); 
    c.b(); 
    c.c(); 
    c.d(); 
    c.e();
    c.f();
    
    cout << endl;
    A* pa = &c;
    pa->a(); 
    pa->b(); 
    pa->c(); 
    //pa->d();
    pa->e(); 
    //pa->f();
    
    cout << endl;
    B* pb = &c;
    pb->a(); 
    //pb->b(); 
    pb->c(); 
    pb->d();
    //pb->e();
    pb->f(); 

    cout << endl;
    C * pc = &c;
    pc->a(); 
    pc->b(); 
    pc->c(); 
    pc->d(); 
    pc->e();
    pc->f();
}

int main(){
	test0();
	return 0;
}
