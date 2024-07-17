#include <math.h>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::pair;

template <typename Container>
void display(const Container &con){
	for(auto elem : con){
		cout << elem << " ";
	}
	cout << endl;
}

//version1: overload operator <
class Point{
public:
	Point(int x,int y)
	:_ix(x)
	,_iy(y)
	{}

	float getDistance()const{
		return pow((_ix*_ix+_iy*_iy),0.5);
	}

	int getx()const{
		return _ix;
	}

	int gety()const{
		return _iy;
	}

	friend
	std::ostream& operator<<(std::ostream &os,const Point &rhs);

	friend
	bool operator<(const Point& lhs,const Point& rhs);	

	friend struct ComparePoint;
private:
	int _ix;
	int _iy;
};

std::ostream& operator<<(std::ostream &os,const Point &rhs){
	os << "(" << rhs._ix << "," << rhs._iy << ")"; 
	return os;
}

bool operator<(const Point& lhs,const Point& rhs){
	float a = lhs.getDistance(); 
	float b = rhs.getDistance();
	if(a < b){
		return true;
	}else if(a == b){
		if(lhs._ix < rhs._ix) return true;
	}
	return false;
}

//version2: 
struct ComparePoint{
	bool operator()(const Point& lhs,const Point& rhs) const{
		cout << "compare point" << endl;
		float a = lhs.getDistance(); 
		float b = rhs.getDistance();
		if(a < b){
			return true;
		}else if(a == b){
			if(lhs._ix < rhs._ix) return true;
		}
			return false;
		}
};

//version3: template specialy
namespace std{
template<>
struct less<Point>{
	bool operator()(const Point& lhs,const Point& rhs) const{
		cout << "template<>" << endl;
		float a = lhs.getDistance(); 
		float b = rhs.getDistance();
		if(a < b){
			return true;
		}else if(a == b){
			if(lhs.getx() < rhs.getx()) return true;
		}
			return false;
		}
};
}

void test0(){
	set<Point,ComparePoint> p = {
		Point(1,2),
		Point(-1,2),
		Point(1,-2),
		Point(2,2),
		Point(1,2),
		Point(3,2),
	};
	display(p);	
}

int main(){
	test0();
	return 0;
}
