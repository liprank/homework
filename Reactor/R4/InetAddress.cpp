/**
 * Project reactor
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
	::bzero(&_addr,sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

/**
 * @param addr
 */
InetAddress::InetAddress(const struct sockaddr_in & addr) 
:_addr(addr)
{

}

InetAddress::~InetAddress() {

}

/**
 * @return string
 */
string InetAddress::ip() const{
    return string(inet_ntoa(_addr.sin_addr));
}

/**
 * @return unsigned short
 */
unsigned short InetAddress::port() const{
    return ntohs(_addr.sin_port);
}

/**
 * @return struct sockaddr_in *
 */
const struct sockaddr_in * InetAddress::getInetAddressPtr() const{
	return &_addr;
}
