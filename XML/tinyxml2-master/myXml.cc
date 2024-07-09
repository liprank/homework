#include "tinyxml2.h"
#include <iostream>
#include <string.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
 }; 

 int example_1(){
	XMLDocument doc;
	doc.LoadFile("resources/coolshell.xml");

	static const char* xml = "<element/>";
	doc.Parse(xml);

	return doc.ErrorID();
 }

 int main(){
	example_1();
	return 0;
 }
