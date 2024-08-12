/**
 * Project Reactor
 */


#include "InetAddress.h"
#include <strings.h>

/**
 * InetAddress implementation
 */


/**
 * @param ip
 * @param port
 */
InetAddress::InetAddress(const string & ip, unsigned short port) {
	bzero(&_addr,sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const sockaddr_in& addr)
:_addr(addr)
{

}

InetAddress::~InetAddress() {

}

/**
 * @return string
 */
string InetAddress::getIp() const{
    return string(inet_ntoa(_addr.sin_addr));
}

/**
 * @return unsigned short
 */
unsigned short InetAddress::getPort() const{
    return ntohs(_addr.sin_port);
}

