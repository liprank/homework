#include <iostream>
#include <fstream>
#include <sstream>

#include <map>
#include <set>
#include <vector>
#include <string.h>

using std::cout;
using std::endl;
using std::map;
using std::set;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;

class TextQuery{
public:
	void read(const string &filename);
	void store(const string & filename);
	void query(const string & word);

private:
	vector<string> _lines;
	map<string,set<int>> _wordNumbers;
	map<string,int> _dict;
};

void TextQuery::read(const string & filename){
	ifstream ifs(filename);	
	if(!ifs){
		cerr << "ifstream open ifs failed" << endl;
		return;
	}

	string line;
	string word;
	int lineNumber = -1;
	while(getline(ifs,line)){
		istringstream iss(line);
		_lines.push_back(line);//记录原始文本

		lineNumber++;
		while(iss >> word,!iss.eof()){
			if(std::isdigit(word[0]) || word.size() == 1){
				continue;
			}else{
				++_dict[word];
				_wordNumbers[word].insert(lineNumber);//对应word中插入行号
			}
		}
	}

	ifs.close();
}

//返回该单词出现的所有行号
void TextQuery::query(const string & word){
	auto it = _wordNumbers.find(word);	
	if(it == _wordNumbers.end()){
		cout << "该元素不在map中" << endl;
	}else{
		cout << word << " " << "occurs "<<_dict[word] << "times" << endl;
		auto i = it->second;
		for(auto &l : i){
			cout << "(line" << l << ") " << _lines[l] << endl;
		}
	}
}

int main(){
	string queryWord("god");
	TextQuery tq;
	tq.read("The_Holy_Bible.txt");
	tq.query(queryWord);

	return 0;
}
