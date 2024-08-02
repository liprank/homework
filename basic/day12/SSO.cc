#include <iostream>
#include <string.h>

using std::ostream;
using std::cout;
using std::endl;

class String{
public:
	String(const char* pstr);
	~String();
	char & operator[](size_t idx);

	friend
	ostream & operator<<(ostream & os,const String & rhs);

	void print(){
		cout << "size: " << _size << endl;
		cout << "capacity: " << _capacity << endl;
	}
private:
	union Buffer{
		char * _pointer = nullptr;
		char _local[16];
	};

	size_t _size;
	size_t _capacity;
	Buffer _buffer;
};

String::String(const char* pstr)
:_size(strlen(pstr))
{
	if(_size > 15){
		_capacity = _size;

		if(nullptr != _buffer._pointer){
			delete [] _buffer._pointer;
		}
		_buffer._pointer = new char[_capacity +1]();
		strcpy(_buffer._pointer,pstr);
	}
	else{
		_capacity = 15;
		strcpy(_buffer._local,pstr);
	}
}

String::~String(){
	if(_size > 15){
		delete [] _buffer._pointer;	
		_buffer._pointer = nullptr;
	}
	cout << "~String" << endl;
}

char & String::operator[](size_t idx){
	if(idx > _size){
		cout << "out of range" << endl;
		static char nullchar = '\0';
		return nullchar;
	}

	if(_size > 15){
		return _buffer._pointer[idx];	
	}else{
		return _buffer._local[idx];
	}
}

void test0(){
	String s1("hello");	
	s1.print();	

	String s2("hello world!!!!!");
	s2.print();

	cout << s1[0] << endl; 
	s1[0] = 'H';

	cout << s1 << endl;
	cout << s2 << endl;

}

ostream & operator<<(ostream & os,const String & rhs){
	if(rhs._size < 15){
		os << rhs._buffer._local;
	}else{
		os << rhs._buffer._pointer;
	}

	return os;
}

int main(){
	test0();
	return 0;
}
