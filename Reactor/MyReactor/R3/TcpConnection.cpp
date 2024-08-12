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

void TcpConnection::NewConnectionCB(TcpCB && cb){
	_onNewConnectionCB = std::move(cb);
}

void TcpConnection::MessageCB(TcpCB && cb){
	_onMessageCB = std::move(cb);
}

void TcpConnection::CloseCB(TcpCB && cb){
	_onCloseCB = std::move(cb);
}

void TcpConnection::NewConnectionHandle(){
	if(_onNewConnectionCB){
		_onNewConnectionCB(shared_from_this());
	}else{
		cout << "NewConnectionCB is nullptr" << endl;
	}
}

void TcpConnection::MessageHandle(){
	if(_onMessageCB){
		_onMessageCB(shared_from_this());
	}else{
		cout << "MessageCB is nullptr" << endl;
	}
}

void TcpConnection::CloseHandle(){
	if(_onCloseCB){
		_onCloseCB(shared_from_this());
	}else{
		cout << "CloseCB" << endl;
	}
}

bool TcpConnection::isClosed() const{
	char buf[10] = {0};
	int ret = ::recv(_sock.getFd(),buf,sizeof(buf),MSG_PEEK);

	return 0 == ret;
}





