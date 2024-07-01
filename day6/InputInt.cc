#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::endl;

//void InputInit(int & num){
//	cout << "please input a number" << endl;
//	cin >> num;
//	while(!cin.eof()){
//		if(cin.bad()){
//			cout << "Input is broken" << endl;
//			return;
//		}else if(cin.fail()){
//			cin.clear();
//			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');	
//			cout << "please input a number!!" << endl;
//			cin >> num;
//		}else{
//			cout << "num:" << num << endl;
//			break;
//		}
//	}
//}

void InputInit(int & num){
	cout << "please input a number" << endl;
	while(cin >> num, !cin.eof()){
		if(cin.bad()){
			cout << "Input is broken" << endl;
			return;
		}else if(cin.fail()){
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');	
			cout << "please input a number!!" << endl;
			//cin >> num;
		}else{
			cout << "num:" << num << endl;
			break;
		}
	}
}


void test0(){
	int num = 0;
	InputInit(num);
}

int main(){
	//char* str;
	//cin >> str;
	//cout << str;
	char a[200] = {0}; 
	cin.getline(a,200,' ');
	cout << a;
	test0();
	return 0;
}
