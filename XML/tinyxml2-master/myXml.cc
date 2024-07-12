#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;
using std::cerr;
using std::regex;

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
	XMLDocument doc;
 }; 

 int example_1(){
	XMLDocument doc;
	doc.LoadFile("resources/coolshell.xml");

	static const char* xml = "<element/>";
	doc.Parse(xml);

	return doc.ErrorID();
 }

RssReader::RssReader(){
	doc.LoadFile( "resources/coolshell.xml" );
}

void RssReader::parseRss()
{
	XMLNode* declaration = doc.FirstChild();
	XMLNode* rss = declaration->NextSibling(); 
	XMLElement* rssElement = rss->ToElement();

	int times = 1;
	XMLElement* itemElement = rssElement->FirstChildElement("channel")->FirstChildElement("item"); 
	
	while(itemElement){
		XMLElement* titleElement = itemElement->FirstChildElement("title");
		XMLElement* linkElement = itemElement->FirstChildElement("link");
		XMLElement* descriptionElement = itemElement->FirstChildElement("description");
		XMLElement* contentElement = itemElement->FirstChildElement("content:encoded");

		XMLText* textNode0 = titleElement->FirstChild()->ToText();
		XMLText* textNode1 = linkElement->FirstChild()->ToText();
		XMLText* textNode2 = descriptionElement->FirstChild()->ToText();
		XMLText* textNode3 = contentElement->FirstChild()->ToText();
		
		const char* title = textNode0->Value();
		const char* link = textNode1->Value();
		const char* description = textNode2->Value();
		const char* content = textNode3->Value();

		regex re1(R"(<p>|</p>|</li>|</ul>|<h4>|</h4>|<div>|</div>)");
		regex re2(R"(<ul>)");
		regex re3("<li>");
		//regex re2("</p>");
		string descriptionR1 = std::regex_replace(description,re1,"");
		string contentR1 = std::regex_replace(content,re1,"");
		
		string descriptionR2 = std::regex_replace(descriptionR1,re2,"\n");
		string contentR2 = std::regex_replace(contentR1,re2,"\n");

		string descriptionR3 = std::regex_replace(descriptionR2,re3,"->");
		string contentR3 = std::regex_replace(contentR2,re3,"->");

		RssItem rssItem;
		rssItem.title = title;
		rssItem.link = link;
		rssItem.description = descriptionR3;
		rssItem.content = contentR3;
		_rss.push_back(rssItem);

		printf( "title: %s\n", title );
		printf( "link: %s\n", link );
		printf( "description: %s\n", description );
		printf( "content: %s\n", content );

		//rss = rss->NextSibling(); 
		//rssElement = rss->ToElement();
		itemElement = itemElement->NextSiblingElement();
		if(itemElement == nullptr) cout << "itemElement is null" <<" times:" << times << endl;
		times++;
	}
		//return doc.ErrorID();
}

void RssReader::dump(const string& filename){
	ofstream output(filename,std::ios::out);	

	int docid = 1;
	for(auto item : _rss){
		output << "<doc>"<< endl;
		output << "\t" << "<docid>" << docid << "</docid>" << endl;
		output << "\t" << "<title>" << item.title << "</title>" << endl;
		output << "\t" << "<link>" << item.link << "</link>" << endl;
		output << "\t" << "<description>" << item.description << "</description>"<< endl;
		output << "\t" << "<content>" << item.content << "</content>" << endl;
		output << "</doc>" << endl;

		docid++;
	}

	output.close();
	cout << "file written successfully!" << endl;
}

 int main(){
	RssReader reader;
	reader.parseRss();
	reader.dump("myxml.txt");
	return 0;
 }
