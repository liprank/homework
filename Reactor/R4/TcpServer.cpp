/**
 * Project reactor
 */


#include "TcpServer.h"

/**
 * TcpServer implementation
 */


/**
 * @param ip
 * @param port
 */
TcpServer::TcpServer(const string & ip, unsigned short port) 
:_acceptor(ip,port)
,_loop(_acceptor)
{

}

TcpServer::~TcpServer(){

}

/**
 * @return void
 */
void TcpServer::start() {
	_acceptor.ready();
	_loop.loop();
}

/**
 * @return void
 */
void TcpServer::stop() {
	_loop.unloop();
}

/**
 * @param cb1
 * @param cb2
 * @param cb3
 * @return void
 */

//注册三个回调函数
void TcpServer::setAllCallback(TcpConnectionCallback && cb1, TcpConnectionCallback && cb2, TcpConnectionCallback && cb3) {
	_loop.setNewConnectionCallback(std::move(cb1));
	_loop.setMessageCallback(std::move(cb2));
	_loop.setCloseCallback(std::move(cb3));
}

