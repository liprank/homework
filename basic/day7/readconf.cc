#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;

void readConfig(const string & filename){
	ifstream ifs(filename);
	if(!ifs){
		cerr << "ifstream open file failed" << endl;
		return;
	}

	string line;
	string key;
	string value;
	while(getline(ifs,line)){
		istringstream iss(line);
		iss >> key >> value;
		cout << key << "----->" << value << endl;
	}

}

int main(){
	readConfig("server.conf");
	return 0;
}
