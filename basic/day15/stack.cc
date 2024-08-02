#include <iostream>

using std::cout;
using std::endl;

template <class T,int kCapacity = 10>
class Stack{
public:
 Stack()
    : _top(-1)
    , _data(new T[kCapacity]())
    {
        cout << "Stack()" << endl;
    }

    ~Stack(){
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
        cout << "~Stack()" << endl;
    }

    bool empty() const{
		return _top == -1;
	}

    bool full() const{
		return _top == kCapacity-1;
	}

    void push(const T & element){
		_data[++_top] = element;	
	}

    void pop(){
		--_top;
	}
	
    T top(){
		return _data[_top];
	}

private:
	int _top;
	T* _data;
};
