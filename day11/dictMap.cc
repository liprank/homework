#include <iostream>
#include <fstream>
#include <sstream>

#include <map>
#include <string.h>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;

class Dictionary{
public:
	void read(const string &filename);
	void store(const string & filename);

private:
	map<string,int> _dict;
};

void Dictionary::read(const string & filename){
	ifstream ifs(filename);	
	if(!ifs){
		cerr << "ifstream open ifs failed" << endl;
		return;
	}

	string line;
	string word;

	while(getline(ifs,line)){
		istringstream iss(line);
		while(iss >> word,!iss.eof()){
			if(std::isdigit(word[0]) || word.size() == 1){
				continue;
			}else{
				_dict[word]++;
			}
		}
	
	}

	ifs.close();
}

void Dictionary::store(const string& filename){
	ofstream ofs(filename);
	if(!ofs){
		cerr << "ifstream open ifs failed" << endl;
		return;
	}

	for(auto &word : _dict){
		ofs << word.first << " " << word.second << endl;	
	}

	ofs.close();
}

int main(){
	Dictionary bible;	
	bible.read("The_Holy_Bible.txt");
	bible.store("Dictionary");
}
