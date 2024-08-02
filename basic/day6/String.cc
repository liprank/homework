#include <iostream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;

class String
{
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print();
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

//构造函数没有返回值
String::String(){
	_pstr = new char(); 
	cout << "String()" << endl;
}

//拷贝构造
String::String(const char* pstr){
	_pstr = new char[strlen(pstr) + 1]();
	strcpy(_pstr,pstr);
	cout << "String(const char*)" << endl;
}

String::String(const String &rhs){
	_pstr = new char[strlen(rhs._pstr) + 1]();
	strcpy(_pstr,rhs._pstr);
	cout << "String(const String &rhs)" << endl;
}

String& String::operator=(const String &rhs){
	//检查自赋值
	if(this != &rhs){
		if(_pstr){
			delete [] _pstr;
		}
		_pstr = new char[strlen(rhs._pstr) + 1]();
		strcpy(_pstr,rhs._pstr);
	}
	cout << "operator=" << endl;
	return *this;
}

String::~String(){
	delete [] _pstr;	
	cout << "~String()" << endl;
}

void String::print(){
	cout << _pstr << endl;
}

int main()
{
	String str1;
	str1.print();

	//yingshi zhuanhuan:
	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}
