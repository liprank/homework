/**
 * Project reactor
 */


#ifndef _INETADDRESS_H
#define _INETADDRESS_H

#include <arpa/inet.h>
#include <string>

using std::string;
class InetAddress {
public: 
/**
 * @param ip
 * @param port
 */
InetAddress(const string & ip, unsigned short port);
    
/**
 * @param addr
 */
InetAddress(const struct sockaddr_in & addr);
    
~InetAddress();
    
string ip() const;
    
unsigned short port() const;
    
const struct sockaddr_in * getInetAddressPtr() const;

private:
struct sockaddr_in _addr;

};

#endif //_INETADDRESS_H
