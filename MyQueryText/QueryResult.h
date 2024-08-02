#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include <iostream>
#include <memory>
#include <string>
#include <set>
#include <vector>

using std::string;
using std::set;
using std::vector;
using std::shared_ptr;
using std::ostream;

class QueryResult{
	friend ostream& print(ostream&,const QueryResult&);
public:
typedef size_t line_no; 
typedef std::set<line_no>::const_iterator line_it;

	QueryResult(string s,shared_ptr<set<line_no>> l,shared_ptr<vector<string>> f)
	:sought(s)
	,lines(l)
	,file(f)
	{}

	size_t size() const{
		return lines->size();
	}

	line_it begin() const{
		return lines->begin();
	}

	line_it end() const{
		return lines->end();
	}

	shared_ptr<vector<string>> get_file(){
		return file;
	}

private:
	string sought;//查询词
	shared_ptr<set<line_no>> lines;//所在行数
	shared_ptr<vector<string>> file;//所有文件内容
};

#endif
