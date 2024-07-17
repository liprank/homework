#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include "QueryResult.h"
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

class TextQuery{
public:
	using line_no = std::vector<std::string>::size_type;

	//file in stream
	TextQuery(std::ifstream &);

	//save the result
	QueryResult query(const std::string&) const;

	//print the map
	void display_map();
private:
	//file will be loaded in vector
	std::shared_ptr<std::vector<std::string>> file;

	//maps each word to the lines in which that word appers
	std::map<std::string,std::shared_ptr<std::set<line_no>>> wm;

	//remove punctuation and makes everything lower case
	static std::string cleanup_str(const std::string&);
};


#endif
