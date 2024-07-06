#include "mylog.hh"
#include <iostream>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

using std::cout;
using std::endl;
using namespace log4cpp;

Mylogger* _pInstance = nullptr;

Mylogger::Mylogger()
:_category(Category::getRoot().getInstance("cate"))
{
	auto ptn1 = new PatternLayout(); 	
	ptn1->setConversionPattern("%d %c [%p] %m%n");

	auto ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d %c [%p] %m%n");

	auto pos = new OstreamAppender("console",&cout);
	pos->setLayout(ptn1);

	auto pfile = new FileAppender("fle","mylogger");
	pfile->setLayout(ptn2);

	_category.setPriority(Priority::DEBUG);
	_category.addAppender(pos);
	_category.addAppender(pfile);

	cout << "Mylogger" << endl;
}

Mylogger::~Mylogger(){
	Category::shutdown();
	cout << "~Mylogger" << endl;
}

Mylogger* Mylogger::getInstance(){
	if(nullptr == _pInstance){
		_pInstance = new Mylogger();
	}

	return _pInstance;
}

void Mylogger::destroy(){
	if(_pInstance){
		delete _pInstance;
		_pInstance = nullptr;
	}
}

void Mylogger::warn(const char* msg){
	_category.warn(msg);
}











