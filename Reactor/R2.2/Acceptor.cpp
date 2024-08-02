/**
 * Project reactor
 */


#include "Acceptor.h"
#include <stdio.h>
/**
 * Acceptor implementation
 */


/**
 * @param ip
 * @param port
 */
Acceptor::Acceptor(const string & ip, unsigned short port) 
:_sock()
,_addr(ip,port)
{

}

Acceptor::~Acceptor() {

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
 * @return int
 */
int Acceptor::accept() {
	int connfd = ::accept(_sock.fd(),nullptr,nullptr);
	if(-1 == connfd)
    {
        perror("accept");
        return -1;
    }
    return connfd;
}

/**
 * @return void
 */
void Acceptor::setReuseAddr() {
	int on = 1;
	int ret = setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret){
		perror("setsockopt");
		return;
	}
}

/**
 * @return void
 */
void Acceptor::setReusePort() {
	int on = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if(-1 == ret)
    {
        perror("setsockopt");
        return;
    }
}

/**
 * @return void
 */
void Acceptor::bind() {
	int ret = ::bind(_sock.fd(),(struct sockaddr *)_addr.getInetAddressPtr(),sizeof(struct sockaddr));
	if(-1 == ret){
		perror("bind");
		return;
	}
}

/**
 * @return void
 */
void Acceptor::listen() {
	int ret = ::listen(_sock.fd(),128);
	if(-1 == ret){
		perror("listen");
		return;
	}
}

int Acceptor::getFd() const{
	return _sock.fd();
}
