#ifndef QUERY_H
#define QUERY_H
#include "TextQuery.h" 
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

class Query_base{
friend class Query;
protected:
	typedef TextQuery::line_no line_no;
	virtual ~Query_base(){}
private:
	//return the queryresult
	virtual QueryResult eval(const TextQuery&) const = 0;

	//represent the query
	virtual std::string rep() const = 0;
};

//interface class to manage the query_base inheritance hierarchy
class Query{

public:
	//build a new wordquery
	Query(const std::string&);

	QueryResult eval(const TextQuery &t) const{
		return q->eval(t);
	}

	std::string rep() const{
		return q->rep();
	}

private:
	Query(std::shared_ptr<Query_base> query)
	: q(query)
	{

	}
	std::shared_ptr<Query_base> q;
};
inline std::ostream &operator<<(std::ostream &os,const Query &query){
	return os << query.rep();
}

class WordQuery
:public Query_base
{
	friend class Query;
	WordQuery(const std::string &s)
	: query_word(s)
	{

	}

	QueryResult eval(const TextQuery &t) const{
		return t.query(query_word);
	}

	std::string rep() const{
		return query_word;
	}

	std::string query_word;
};
#endif
