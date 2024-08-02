#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include "QueryResult.h"
#include <map>
#include <fstream>

using std::ifstream;

using std::map;

class TextQuery{
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);//接受文件
	QueryResult query(const string&)const;//返回查询结果

private:
	shared_ptr<vector<string>> file;//store each line in the file
	map<string,shared_ptr<set<line_no> >> wm;
	static string cleanup_str(const string&);
};
#endif
