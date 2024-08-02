/**
 * Project Reactor
 */


#include "TcpConnection.h"

/**
 * TcpConnection implementation
 */


/**
 * @param fd
 */
void TcpConnection::TcpConnection(int fd) {

}

void TcpConnection::~TcpConnection() {

}

/**
 * @param const string &
 * @return int
 */
int TcpConnection::send(void const string &) {
    return 0;
}

/**
 * @return string
 */
string TcpConnection::receive() {
    return "";
}

/**
 * @return InetAddress
 */
InetAddress TcpConnection::getlocalAddr() {
    return null;
}

/**
 * @return InetAddress
 */
InetAddress TcpConnection::getpeerAddr() {
    return null;
}