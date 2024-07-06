// main.cpp

#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
using namespace log4cpp;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
	//1.设置布局
	PatternLayout * ptn1 = new PatternLayout();
	ptn1->setConversionPattern("%d %c [%p] %m%n");

	PatternLayout* ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d %c [%p] %m%n");

	PatternLayout* ptn3 = new PatternLayout();
	ptn3->setConversionPattern("%d %c [%p] %m%n");

	//2.设置目的地
	OstreamAppender *appender1 = new OstreamAppender("console", &cout);
	appender1->setLayout(ptn1);

	auto pfile = new FileAppender("file","wd.log");
	pfile->setLayout(ptn2);


	//3.创建记录器
	Category& root = Category::getInstance("root");
	root.setPriority(Priority::WARN);
	root.addAppender(appender1);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << Priority::ERROR << "Streamed root error";
	root << Priority::INFO << "Streamed root info";

	// or this way:
	root.errorStream() << "Another streamed error";

	Category::shutdown();
	return 0;
}
