#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::remove_if;
using std::mem_fn;
using std::bind;
using std::function;

class Number
{
public:
    Number(size_t data = 0)
    : _data(data)
    {

    }

    void print() const
    {
        cout << _data << "  ";
    }

    //偶数
    bool isEven() const
    {
        return (0 == _data % 2);
    }

    //质数
    bool isPrime() const
    {
        if(1 == _data)
        {
            return false;
        }

        for(size_t idx = 2; idx <= _data/2; ++idx)
        {
            if(0 == _data % idx)
            {
                return false;
            }
        }

        return true;
    }

    ~Number()
    {

    }
private:
    size_t _data;
};

void test(){
	vector<Number> vec;
	for(size_t idx = 1; idx != 30; ++idx){
		vec.push_back(Number(idx));
	}

	using namespace std::placeholders;
	function<void(Number)> f = bind(&Number::print,_1);
	for_each(vec.begin(),vec.end(),f);
	cout << endl;

	//删除所有的偶数
	auto it = remove_if(vec.begin(),vec.end(),mem_fn(&Number::isEven));
	vec.erase(it,vec.end());	
	for_each(vec.begin(),vec.end(),f);
	cout << endl;
}

int main(){
	test();
	return 0;
}
