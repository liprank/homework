/**
 * Project Reactor
 */


#include "EchoServer.h"
#include <iostream>

using std::cout;
using std::endl;

/**
 * EchoServer implementation
 */


/**
 * @param threadNum
 * @param queSize
 * @param ip
 * @param port
 */
EchoServer::EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port) 
:_pool(threadNum,queSize)
,_server(ip,port)
{

}

EchoServer::~EchoServer() {

}

/**
 * @param con
 * @return void
 */
void EchoServer::onNewConnection(const TcpConnectionPtr & con) {
	cout << con->toString() << " has connected" << endl;
}

/**
 * @param con
 * @return void
 */
void EchoServer::onMessage(const TcpConnectionPtr & con) {
	//接收客户端的数据
    string msg = con->receive();
    cout << ">>recv msg from client: " << msg << endl;

    MyTask task(msg, con);

    _pool.addTask(std::bind(&MyTask::process, task));
}

/**
 * @param con
 * @return void
 */
void EchoServer::onClose(const TcpConnectionPtr & con) {
	cout << con->toString() << " has closed" << endl;
}

/**
 * @return void
 */
void EchoServer::start() {
   _pool.start();
   //注册所有的回调
    using namespace std::placeholders;
    _server.setAllCB(std::bind(&EchoServer::onNewConnection, this, _1)
                           , std::bind(&EchoServer::onMessage, this, _1)
                           , std::bind(&EchoServer::onClose, this, _1));

    _server.start();
}

/**
 * @return void
 */
void EchoServer::stop() {
	_pool.stop();
	_server.stop();
}

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con)
: _msg(msg)
, _con(con)
{

}
void MyTask::process()
{
    //处理业务逻辑
    _con->sendInLoop(_msg);
}
