#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Student{
public:
	Student(int id, double height, const char* name, double score)
	:_id(id)
	,_height(height)
	,_name(new char[strlen(name)+1]())
	,_score(score)
	{
		strcpy(_name,name);
		cout<<'('<< _id << ',' 
			<< _height << ','
			<< _name << ','
			<< _score << ')' << endl;
	}

	~Student(){
		if(_name){
			delete [] _name;
			_name = nullptr;
		}
		cout << "~Student()" << endl;
	}

private:
	int _id;
	double _height;
	char* _name;
	double _score;
};



int main(){
	Student sd(1,173.3,"tang",98.9);
}
