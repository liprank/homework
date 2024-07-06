#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string.h>
using std::string;
using std::vector;
using std::istringstream;
using std::ifstream;
using std::ofstream;
using std::cerr;

using std::cout;
using std::endl;
using std::find;
using std::distance;

struct Record{
	string _word;
	int _frequency;
};

class Dictionary{
public:
	void read(const string &filename);
	void store(const string &filename);

private:
	vector<Record> _dict;
	vector<string> _wordArray;
	vector<int> _wordCount;
};

bool compareRecords(const Record &a, const Record &b) {
    return a._word < b._word;
}

void Dictionary::read(const string &filename){
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
			}

			auto it = find(_wordArray.begin(),_wordArray.end(),word);
			if(it == _wordArray.end()){
				_wordArray.push_back(word);
				_wordCount.push_back(1);

			}else{
				//i = find(vector,word)				
				//wordCount[i]++
				//找到索引
				size_t index = distance(_wordArray.begin(),it);
				_wordCount[index]++;
			}
		}
	}
}

void Dictionary::store(const string &filename){
	ofstream ofs(filename);
	if(!ofs){
		cerr << "ofstream open file failed" << endl;
		return;
	}
	int length = _wordArray.size(); 
	for(int i = 0; i < length; i++){
		Record temp;
		temp._word = _wordArray[i];
		temp._frequency = _wordCount[i];
		_dict.push_back(temp);
	}

	std::sort(_dict.begin(),_dict.end(),compareRecords);

	for(int i = 0; i < length; i++){
		ofs << _dict[i]._word << " " << _dict[i]._frequency << endl; 	
	}

	ofs.close();
}

int main(){
	Dictionary bible;
	bible.read("The_Holy_Bible.txt");
	bible.store("Dictionary");
}

