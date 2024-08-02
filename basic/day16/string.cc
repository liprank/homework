#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::string;

class String{
public:
	String()
	:_pstr(new char[1]())
	{}

	String(const char* pstr)
	:_pstr(new char[strlen(pstr)+1]())
	{
		cout << "copy(const char*)" << endl;
		strcpy(_pstr,pstr);
	}

	String(String && rhs)
	:_pstr(rhs._pstr)
	{
		cout << "move(String &&)" << endl;
		rhs._pstr = nullptr;
	}

	String & operator=(const String &&rhs){
		cout << "copy operator=" << endl;
		if(this != &rhs){
			if(_pstr){
				delete [] _pstr;
			}
			_pstr = new char[strlen(rhs._pstr)+1]();
			strcpy(_pstr,rhs._pstr);
		}
		return *this;
	}

	~String()
    {
        cout << "~String()" << endl;
        if(_pstr)
        {
            delete [] _pstr;
            _pstr = nullptr;
        }
    }
private:
	char* _pstr;
};

int main(){
	String s1 = "hello";
	String s2("world1");
	s2 = String(std::move(s1));
	String s3 = std::move(s1);
}


