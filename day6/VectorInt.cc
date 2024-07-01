#include <vector>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(){
	vector<vector<int>> array{{1,3},{1,2,3},{1,2,3,4},{1,2,3}};
	for(auto &elem : array){
		for(auto &num : elem){
			cout << num << " ";
		}
		cout << endl;
	}

	return 0;
}
