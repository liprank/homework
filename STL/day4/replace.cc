#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;

class Replace{
public:
	ifstream openfile(string filename);  
	void readword(string filename);
	void replace(string filename1,string filename2);
	void display()const;
private:
	map<string,string> _m1;
};

ifstream Replace::openfile(string filename){
	ifstream ifs(filename);	
	if(!ifs){
		cerr << "ifstream open ifs failed" << endl;
	}
	return ifs;
}

void Replace::display()const{
	for(auto elem : _m1){
		cout << elem.first << " "<<elem.second << endl;
	}
}

void Replace::readword(string filename){
	ifstream ifs = openfile(filename);
	string line;
	string first,remaining;
	while(getline(ifs,line)){
		istringstream iss(line);
		iss >> first;
		getline(iss,remaining);
		_m1[first] = remaining.substr(1);
	}
}

void Replace::replace(string filename1,string filename2){
	ifstream ifs = openfile(filename1);	
	ofstream ofs(filename2);

	if(!ofs){
		cerr << "ifstream open ofs failed" << endl;
		return;
	}

	string line;
	string word;
	while(getline(ifs,line)){
		istringstream iss(line);
		while(iss >> word){
			if(_m1.find(word) != _m1.end()){
				ofs << _m1[word] << " ";
			}else{
				ofs << word << " ";
			}
		}
		ofs << endl;
	}
}

int main(){
	Replace r1;
	r1.readword("map.txt");
	r1.replace("file.txt","result.txt");
	r1.display();
}
