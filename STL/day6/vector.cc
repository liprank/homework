#include <iostream>

using std::cout;
using std::endl;

template<typename T>
class Vector
{
public:
    Vector();
    ~Vector();
    void push_back(const T &);
    void pop_back();
    int size();
    int capacity();

	int& operator[](int idx){
		int n = size();
		if(idx > n){
			throw std::out_of_range("Segmentation fault");
		}

		return _start[idx];
	}
private:
    void reallocate();//重新分配内存,动态扩容要用的
private:
    static std::allocator<T> _alloc;//定义一个配置器类型的变量
    T *_start;                 //指向数组中的第一个元素
    T *_finish;                //指向最后一个实际元素之后的那个元素
    T *_end_of_storage;        //指向数组本身之后的位置
};

template<typename T>
std::allocator<T> _alloc.construct();

template<typename T>
Vector<T>::Vector(){
	//配置一个元素	
	//start指针指向这个元素
	_start = _alloc.allocate(8);//分配空间为8的倍数
	_finish = _start;
	_end_of_storage = _start + 7;
}

template<typename T>
Vector<T>::~Vector(){
	delete [] _start;//删除_start指向的空间
}

template<typename T>
int Vector<T>::size(){
	return _finish - _start;
}

template<typename T>
int Vector<T>::capacity(){
	return _finish - _start;
}

template<typename T>
void Vector<T>::push_back(const T& value){
	//如果申请的空间够用
	if(_finish != _end_of_storage){
		*_finish++ = value;//将值插入到尾部	
	}else if(_finish == _end_of_storage){
		reallocate();			
		*_finish++ = value;//将值插入到尾部	
	}
}

template<typename T>
void Vector<T>::pop_back(){
	int n = size();
	if(0 == n) return;
	else{
		--_finish;//移动finish指针
	}
}

template<typename T>
void Vector<T>::reallocate(){
	//如果已经到达了尾部，需要进行扩容，将原有元素拷贝过去
	int n = size();
	T* it = _start;
	_start = _alloc.allocate(2*n);//start指向新分配的两倍空间
	T* temp = _start;
	for(int i = 0; i < n; ++i){
		*temp++ = *it++;//将原来空间进行拷贝
	}
	_finish = ++temp;//重新移动_finish;
		
	temp = _start;
	_end_of_storage = temp + 2*n -1;//重新移动_end 
}

void test(){
	Vector<int> v1;
	v1.push_back(10);
	v1.push_back(9);
	v1.push_back(8);
	v1.push_back(7);
	v1.push_back(6);
	v1.push_back(5);
	v1.push_back(4);
	v1.push_back(3);
	v1.push_back(2);

	v1.push_back(1);
	v1.push_back(0);

	for(int i = 0; i < 10; ++i){
		cout << v1[i] << " " << endl;
	}
}

int main(){
	test();
	return 0;
}

