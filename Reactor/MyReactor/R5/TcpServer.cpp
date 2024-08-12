/**
 * Project Reactor
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

TcpServer::~TcpServer() {

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

void TcpServer::setAllCB(TcpCB &&cb1,TcpCB &&cb2,TcpCB &&cb3) {
	_loop.NewConnectionCB(std::move(cb1));	
	_loop.MessageCB(std::move(cb2));	
	_loop.CloseCB(std::move(cb3));	
}
