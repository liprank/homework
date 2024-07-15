#include <iostream>
using namespace std;

int count(int num){
	if(num == 0){
		return 0;
	}

	int count = 0;

	while(num > 0){
		int temp = num % 2;	
		if(temp == 1) count++;
		num = num/2;
	}

	return count; 
}

int main(){
	int res = count(1024);
	cout << res << endl;
}
