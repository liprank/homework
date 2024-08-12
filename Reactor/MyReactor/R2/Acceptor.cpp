/**
 * Project Reactor
 */


#include "Acceptor.h"

/**
 * Acceptor implementation
 */


/**
 * @return void
 */
int Acceptor::accept() {
	int connfd = ::accept(_sock.getFd(),nullptr,nullptr);
	if(-1 == connfd){
		perror("accept");
		return -1;
	}
	return connfd;
}

/**
 * @return void
 */
void Acceptor::ready() {
	setReuseAddr();
	setReusePort();
	bind();
	listen();
}

/**
 * @param ip
 * @param port
 */
Acceptor::Acceptor(const string & ip, unsigned short port) 
:_sock()
,_addr(ip,port)
{

}

/**
 * @return void
 */
void Acceptor::setReuseAddr() {
	int on = 1;
	int ret = setsockopt(_sock.getFd(),SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(-1 == ret){
		perror("setsockopt");
		return;
	}
}

/**
 * @return void
 */
void Acceptor::setReusePort() {
	int on = 1;
	int ret = setsockopt(_sock.getFd(),SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));
	if(-1 == ret){
		perror("setsockopt");
		return;
	}
}

Acceptor::~Acceptor() {

}

/**
 * @return void
 */
void Acceptor::bind() {
	int ret = ::bind(_sock.getFd(),(struct sockaddr *)&_addr,sizeof(struct sockaddr));
	if(-1 == ret){
		perror("bind");
		return;
	}
}

/**
 * @return void
 */
void Acceptor::listen() {
	int ret = ::listen(_sock.getFd(),128);
	if(-1 == ret){
		perror("listen");
		return;
	}
}

int Acceptor::getFd(){
	return _sock.getFd();
}
