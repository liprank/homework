/**
 * Project Reactor
 */


#include "TcpConnection.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;
/**
 * TcpConnection implementation
 */


/**
 * @param fd
 */
TcpConnection::TcpConnection(int fd) 
:_localAddr(getlocalAddr())
,_peerAddr(getpeerAddr())
,_sock(fd)
,_sockIO(fd)
{

}

TcpConnection::~TcpConnection() {

}

/**
 * @param const string &
 * @return int
 */
void TcpConnection::send(const string & msg) {
	_sockIO.writen(msg.c_str(), sizeof(msg));
}

/**
 * @return string
 */
string TcpConnection::receive() {
	char buf[65535] = {0};
	_sockIO.readline(buf,sizeof(buf));
	return string(buf);
}

/**
 * @return InetAddress
 */
InetAddress TcpConnection::getlocalAddr() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(sockaddr);
	int ret = getsockname(_sock.getFd(),(struct sockaddr *)&addr,&len);
	if(-1 == ret){
		perror("getsockname");
	}
	return InetAddress(addr);
}

/**
 * @return InetAddress
 */
InetAddress TcpConnection::getpeerAddr() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(sockaddr);
	int ret = getpeername(_sock.getFd(),(struct sockaddr *)&addr,&len);
	if(-1 == ret){
		perror("getsockname");
	}
	return InetAddress(addr);
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.getIp() << ":"
        << _localAddr.getPort() << "---->"
        << _peerAddr.getIp() << ":"
        << _peerAddr.getPort();

    return oss.str();
}
