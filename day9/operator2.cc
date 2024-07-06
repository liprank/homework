#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

class CharArray{
public:
	CharArray(const char* pstr)
	:_capacity(strlen(pstr) + 1)
	,_data(new char[_capacity]())
	{
		strcpy(_data,pstr);
	}

	~CharArray(){
		if(_data){
			delete [] _data;
			_data = nullptr;	
		}
	}

	char & operator[](int idex){
		if(idex >= _capacity - 1){
			cout << "idex is out of range" << endl;
			static char null = '\0';
			return null;
		}
		else{
			return _data[idex];
		}
	}

	const char & operator[](int idex) const{
		if(idex >= _capacity - 1){
			cout << "idex is out of range" << endl;
			static char null = '\0';
			return null;
		}
		else{
			return _data[idex];
		}
	}

private:
	int _capacity;
	char* _data;
};

int main(){
	CharArray arr("hello world");
	arr[0] = 'H';
	cout << arr[0] << endl;

	const CharArray arr1("hello world");
	//arr1[0] = 'W';

	return 0;
}






