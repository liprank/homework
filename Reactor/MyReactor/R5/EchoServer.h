/**
 * Project Reactor
 */


#ifndef _ECHOSERVER_H
#define _ECHOSERVER_H
#include "ThreadPool.h"
#include "TcpServer.h"
#include "TcpConnection.h"

#include <functional>

using std::shared_ptr;

using TcpConnectionPtr = shared_ptr<TcpConnection>;

class MyTask{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con);
    void process();

private:
    string _msg;
    TcpConnectionPtr _con;
};



class EchoServer {
public: 
    ThreadPool _pool;
    TcpServer _server;
    
/**
 * @param threadNum
 * @param queSize
 * @param ip
 * @param port
 */
EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port);

~EchoServer();


/**
 * @param con
 */
void onNewConnection(const TcpConnectionPtr & con);
    
/**
 * @param con
 */
void onMessage(const TcpConnectionPtr & con);
    
/**
 * @param con
 */
void onClose(const TcpConnectionPtr & con);
    
void start();
    
void stop();
};

#endif //_ECHOSERVER_H
