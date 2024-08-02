#ifndef _MyLogger_HH_
#define _MyLogger_HH_

#include <log4cpp/Category.hh>

#define addPrefix(msg) string("[").append(__FILE__)\
		.append(":").append(__func__)\
		.append(":").append(std::to_string(__LINE__))\
		.append("]").append(msg).c_str()

#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg))

class Mylogger{
public:
	void warn(const char* msg);
	void error(const char* msg);
	void debug(const char* msg);
	void info(const char* msg);

	static Mylogger* getInstance();
	static void destroy();

private:
	Mylogger();
	~Mylogger();

private:
	log4cpp::Category &_category;
	static Mylogger* _pInstance;
};


#endif
