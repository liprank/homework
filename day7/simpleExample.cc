// main.cpp

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
using namespace log4cpp;

int main(int argc, char** argv) {
	//appender代表输出器
	//基类指针指向派生类对象
	//第二个参数是一个ostream*，决定了目的地，&cout表示输出到终端
	Appender *appender1 = new OstreamAppender("console", &std::cout);
	//日志布局
	//目的地与日志格式进行了绑定
	appender1->setLayout(new BasicLayout());

	//第二个参数是将日志保存到文件的名字
	auto appender2 = new FileAppender("default", "program.log");
	//输出到终端和文件的格式是一样的
	appender2->setLayout(new BasicLayout());

	//getRoot创建出root级别的Category对象
	Category& root = Category::getRoot();
	//root设置为日志优先级
	root.setPriority(Priority::WARN);
	root.addAppender(appender1);

	
	Category& sub1 = Category::getInstance(std::string("sub1"));
	sub1.addAppender(appender2);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << Priority::ERROR << "Streamed root error";
	root << Priority::INFO << "Streamed root info";
	sub1 << Priority::ERROR << "Streamed sub1 error";
	sub1 << Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}
