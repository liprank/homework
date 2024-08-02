#include "operatorString.hh"
#include <string.h>
#include <iostream>
#include <limits>
#include <vector>

using std::cerr;
using std::istream;
using std::vector;

String::String(const char* pstr)
:_pstr(new char[strlen(pstr)+1]())
{
	strcpy(_pstr,pstr);
}

String::String(const String &rhs)
:_pstr(new char[strlen(rhs._pstr)+1])
{
	strcpy(_pstr,rhs._pstr);
}

String::~String(){
	if(_pstr){
		delete [] _pstr;
		_pstr = nullptr;
	}
}

String & String::operator=(const String & rhs){
	if(*this == rhs){
		delete [] _pstr;
	}
	
	_pstr = new char[strlen(rhs._pstr) + 1];
	strcpy(_pstr,rhs._pstr);
	return *this;
}

String & String::operator=(const char* rhs){
	_pstr = new char[strlen(rhs) + 1];	
	strcpy(_pstr,rhs);
	return *this;
}

String & String::operator+=(const String & rhs){
	int length = strlen(_pstr) + strlen(rhs._pstr);
	char* temp = new char[length + 1]();	
	strcpy(temp,_pstr);
	strcat(temp,rhs._pstr);

	delete [] _pstr;
	_pstr = new char[length + 1];
	strcpy(_pstr,temp);
	delete [] temp;
	return *this;
}

String & String::operator+=(const char* rhs){
	int length = strlen(_pstr) + strlen(rhs);
	char* temp = new char[length + 1]();	
	strcpy(temp,_pstr);
	strcat(temp,rhs);

	delete [] _pstr;
	_pstr = new char[length + 1];
	strcpy(_pstr,temp);
	delete [] temp;
	return *this;
}

char & String::operator[](std::size_t index){
	if(index < strlen(_pstr)-1){
		return _pstr[index];
	}else{
		cout << "out of range" << endl;
		static char null = '\0';
		return null;
	}
}

const char & String::operator[](std::size_t index) const{
	if(index < strlen(_pstr)-1){
		return _pstr[index];
	}else{
		cout << "out of range" << endl;
		static char null = '\0';
		return null;
	}
}

std::size_t String::size() const{
	return strlen(_pstr); 
}

//??
const char* String::c_str() const{
	return _pstr;
}

bool operator==(const String &lhs, const String &rhs)
{
	if(strcmp(rhs._pstr,lhs._pstr) == 0){
		return true;
	}else{
		return false;
	}
}

bool operator!=(const String &lhs, const String &rhs)
{
	if(strcmp(rhs._pstr,lhs._pstr) != 0){
		return true;
	}else{
		return false;
	}
}

bool operator<(const String &lhs, const String &rhs)
{
	if(strcmp(rhs._pstr,lhs._pstr) < 0){
		return true;
	}else{
		return false;
	}
}

bool operator>(const String &lhs, const String &rhs)
{
	if(strcmp(rhs._pstr,lhs._pstr) > 0){
		return true;
	}else{
		return false;
	}
}

bool operator<=(const String &lhs, const String &rhs)
{
	if(strcmp(rhs._pstr,lhs._pstr) <= 0){
		return true;
	}else{
		return false;
	}
}

bool operator>=(const String &lhs, const String &rhs)
{
	if(strcmp(rhs._pstr,lhs._pstr) >= 0){
		return true;
	}else{
		return false;
	}
}

std::ostream & operator<<(std::ostream &os,const String &s){
	os << s._pstr;
	return os;
}

std::istream & operator>>(std::istream &is, String &s){
	//while(is >> s._pstr, !is.eof()){
    //    if(is.bad()){
    //        cerr << "istream has broken!" << endl;
    //        //return;
    //    }else if(is.fail()){
    //        is.clear();
    //        is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    //        cout << "请输入一个char型数据" << endl;
    //    }else{
    //        break;
    //    }
    //}
	//return is;

	if(s._pstr){
		delete [] s._pstr;
		s._pstr = nullptr;
	}

	vector<char> buffer;
	char ch;
	while((ch = is.get()) != '\n'){
		buffer.push_back(ch);
	}

	s._pstr = new char[buffer.size() + 1]();
	strncpy(s._pstr,&buffer[0],buffer.size());

	return is;
}

String operator+(const String & lhs, const String & rhs){
	String temp(lhs);	
	temp += rhs;
	return temp;
}

String operator+(const String & lhs, const char * rhs){
	String temp(lhs);	
	temp += rhs;
	return temp;
}

String operator+(const char * lhs, const String & rhs){
	String temp(lhs);	
	temp += rhs;
	return temp;
}

int main(){
	String str1("anna");
	cout << str1 << endl;

	String str2(str1);
	cout << str2 << endl;

	String str3 = str1;
	cout << str3 << endl;

	String str4 = "belly";
	cout << str4 << endl;

	String str5 = str4;
	cout << str5 << endl;

	str5 += str1;
	cout << str5 << endl;

	str5 += " hello";
	cout << str5 << endl;
	cout << str5[0] << endl;

	const String str6(str5);
	cout << str6[0] << endl;

	cout << str6.size() << endl;
	cout << str6.c_str() << endl;

	if(str6 == str5){
		cout << "yes" << endl;
	}

	if(str6 != str1){
		cout << "yes" << endl;
	}
}
