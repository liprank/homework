#include "TextQuery.h"
#include <iostream>

using std::istringstream;
using std::ostream;
using std::cout;
using std::endl;

typedef shared_ptr<set<TextQuery::line_no>> lineType;

typedef map<string,shared_ptr<set<TextQuery::line_no>>> wmType;

typedef wmType::const_iterator wmIter;

//to lowercase,erase punctation
string TextQuery::cleanup_str(const string &word){
	string ret;
	auto it = word.begin();
	for(;it != word.end();++it){
		if(!ispunct(*it)) ret += tolower(*it);
	}
	return ret;
}

TextQuery::TextQuery(ifstream &is)
: file(new vector<string>)	
{
	string text;
	while(getline(is,text)){
		file->push_back(text);
		int n = file->size()-1;
		istringstream line(text);
		string word;
		while(line >> word){
			word = cleanup_str(word);
			lineType &lines = wm[word];
			if(!lines) lines.reset(new set<line_no>);//new word allocate a new set
			lines->insert(n);
		}
	}
}

QueryResult
TextQuery::query(const string &sought) const{
	static lineType nodata(new set<line_no>);
	wmIter loc = wm.find(cleanup_str(sought));

	if(loc == wm.end())
		return QueryResult(sought,nodata,file);//not found
	else
		return QueryResult(sought,loc->second,file);
}

ostream &print(ostream &os,const QueryResult &qr){
	os << qr.sought << "occurs" << qr.lines->size() << " "
		<< "times" << endl;
	return os;
}


