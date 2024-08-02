#include <iostream>
#include <string>

using std::string;

//1.单一职责原则
//一个类实现一个函数
class figure{
public:
	int area(int x,int y);
};

class draw
:public figure
{
	void drawfigure(int x,int y);
};

//2.开闭原则
//对抽象编程，而不是对具体编程
class figure1{
public:	
	virtual void getarea() const = 0;
};

class circle
:public figure1
{
	void getarea() const;
};

class triangle
:public figure1
{
	void getarea() const;
};

//3.里氏替换原则
//派生类应该能够替换基类，并且替换之后不会产生影响
class user{
public:
	void consume();
};


class Vip
:public user
{
	void consume1();
	void update();
};



//4.依赖倒置原则
//高层的模块不应该依赖底层的模块，它们都应该依赖抽象
class Worker{
	virtual void doYourJob();	
};

class Cooker
:public Worker
{
	void doYourJob() override;
};

class Waiter
:public Worker
{
	void doYourJob() override;
};
//5.接口分离原则
//不应该依赖一个不需要的接口
class home{
	class kitchen;
	class bedroom;
};

class kitchen{
	void getKnife();
	void getBottle();
	void getFire();
};

class bedroom{
	void getsleep();
	void getgame();
};

//6.迪米特法则
//增加中介，最小了解原则
class food{
public:
	double money;
	string name;
	string source;	
	string data;
};

class shopkeeper{
public:
	food tosale;
};

class customer{
public:
	shopkeeper* ask;
};

//7.组合复用原则
//应该多使用关联关系，少使用继承关系
class Food{
	string name;
	double price;
};

class FA
:public Food
{
};

class FB
:public Food
{

};

class person{
public:
	string name;
	Food f;
};

class A
:public person
{
	void getfood();
};

class B
:public person
{
	void getfodd();
};







