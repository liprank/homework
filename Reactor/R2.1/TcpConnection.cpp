/**
 * Project reactor
 */


#include "TcpConnection.h"
#include "iostream"
#include "sstream"

using std::cout;
using std::endl;
using std::ostringstream;
/**
 * TcpConnection implementation
 */


/**
 * @param fd
 */
TcpConnection:: TcpConnection(int fd) 
:_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
,_sockIO(fd)
,_sock(fd)
{

}

TcpConnection::~TcpConnection() {

}

/**
 * @param msg
 * @return void
 */
void TcpConnection::send(const string & msg) {
	_sockIO.writen(msg.c_str(),msg.size());
}

/**
 * @return string
 */
string TcpConnection::receive() {
	char buff[65535] = {0};
	_sockIO.readLine(buff,sizeof(buff));

	return string(buff);
}

/**
 * @return string
 */
string TcpConnection::toString() {
	ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

/**
 * @return InetAddress
 */
InetAddress TcpConnection::getLocalAddr() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	int ret = getsockname(_sock.fd(),(struct sockaddr *)&addr,&len);
	if(-1 == ret){
		perror("getsockname");
	}

	return InetAddress(addr);
}

/**
 * @return InetAddress
 */
InetAddress TcpConnection::getPeerAddr() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	int ret = getpeername(_sock.fd(),(struct sockaddr *)&addr,&len);
	if(-1 == ret){
		perror("getpeername");
	}

	return InetAddress(addr);
}
