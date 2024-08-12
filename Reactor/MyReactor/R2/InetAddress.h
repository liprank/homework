/**
 * Project Reactor
 */


#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include <arpa/inet.h>
#include <string>

using std::string;
class InetAddress {
public: 
    struct sockaddr_in _addr;
    
/**
 * @param ip
 * @param port
 */
InetAddress(const string & ip, unsigned short port);

InetAddress(const struct sockaddr_in &);

~InetAddress();
    
string getIp() const;
    
unsigned short getPort() const;
    
};

#endif //_INETADDRESS_H
