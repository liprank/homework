#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>

using namespace log4cpp;

using std::cout;
using std::endl;

class Mylogger
{
public:
	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);
	void fatal(const char *msg);
	void crit(const char *msg);

	//创建单例函数
	static Mylogger* getInstance();
	static void Destroy();
private:
	Mylogger(){
		_ptn = new PatternLayout();
		_ptn->setConversionPattern("%d %c [%p] %m%n");

		_pos = new OstreamAppender("console",&cout);	
		_pos->setLayout(_ptn);

		_category = &Category::getInstance("Category");

		_category->setPriority(Priority::DEBUG);
		_category->addAppender(_pos);
	}

	~Mylogger(){
		Category::shutdown();
	}
   
   //ban = copy
   Mylogger(const Mylogger&) = delete;
   Mylogger& operator=(const Mylogger&) = delete;
private:
	//记录器，输出器，格式化器,过滤器
	static Mylogger* _myLogger;

	PatternLayout* _ptn;
	OstreamAppender* _pos;
	Category* _category ;
};
Mylogger* Mylogger::_myLogger = nullptr;

Mylogger* Mylogger::getInstance(){
	if(nullptr == _myLogger){
		_myLogger = new Mylogger();
	}
	return _myLogger;
}

void Mylogger::warn(const char* msg){
	(*this->_category).warn(msg);
}

void Mylogger::error(const char* msg){
	(*this->_category).error(msg);
}

void Mylogger::debug(const char* msg){
	(*this->_category).debug(msg);
}

void Mylogger::info(const char* msg){
	(*this->_category).info(msg);
}

void Mylogger::fatal(const char* msg){
	(*this->_category).fatal(msg);
}

void Mylogger::crit(const char* msg){
	(*this->_category).crit(msg);
}

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->warn("The log is warn message");

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
}

void LogInfo(const char* msg){
	Mylogger *log = Mylogger::getInstance();
	cout << "Func:" << __FUNCTION__ << " File:" << __FILE__ << " Line:" << __LINE__ << " ";
	log->info(msg);
}

void LogError(const char* msg){
	Mylogger *log = Mylogger::getInstance();
	cout << "Func:" << __FUNCTION__ << " File:" << __FILE__ << " Line:" << __LINE__ << " ";
	log->error(msg);
}

void LogWarn(const char* msg){
	Mylogger *log = Mylogger::getInstance();
	cout << "Func:" << __FUNCTION__ << " File:" << __FILE__ << " Line:" << __LINE__ << " ";
	log->warn(msg);
}

void LogDebug(const char* msg){
	Mylogger *log = Mylogger::getInstance();
	cout << "Func:" << __FUNCTION__ << " File:" << __FILE__ << " Line:" << __LINE__ << " ";
	log->debug(msg);
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

int main(){
	test1();
	return 0;
}

