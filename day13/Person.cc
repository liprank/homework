#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::string;

class Person{
public:
	Person(const char* name,int age)
	:_name(new char[strlen(name)+1])
	,_age(age)
	{
		strcpy(_name,name);
	}

	~Person(){
		if(_name){
			delete [] _name;
			_name = nullptr;
		}
	}

	void display(){
		cout << "name: " << _name << endl;
		cout << "age: " << _age << endl;
	}

private:
	char* _name;
	int _age;
};

class Employee
:public Person
{
public:
	Employee(const char* name,int age,const char* department,int salary)
	:Person(name,age)
	,_department(new char[strlen(department)+1])
	,_salary(salary)
	{
		strcpy(_department,department);
		allSalary += salary;
		empolyeeNum++;
	}

	~Employee(){
		if(_department){
			delete [] _department;
			_department = nullptr;
		}
	}

	void display(){
		Person::display();
		cout << "department: " << _department << endl;
		cout << "_salary: " << _salary << endl;
	}

	 static double average(){
		if(empolyeeNum != 0){
			return 1.0 * allSalary / empolyeeNum;		
		}

		return -1;
	}

private:
	char* _department;
	int _salary;
	static int allSalary;
	static int empolyeeNum;
};
int Employee::allSalary = 0;
int Employee::empolyeeNum = 0;

void test0(){
	Employee e1("zhao",14,"asd",1234);
	Employee e2("tao",15,"asd",4321);

	e1.display();

	cout << endl;

	e2.display();
	
	cout << "average salary: " << Employee::average() << endl;
}

int main(){
	test0();
	return 0;
}
