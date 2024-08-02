/**
 * Project Reactor
 */


#ifndef _INETADDRESS_H
#define _INETADDRESS_H

class InetAddress {
public: 
    struct sockaddr_in _addr;
    
/**
 * @param ip
 * @param port
 */
void InetAddress(const string & ip, unsigned short port);
    
string getIp();
    
unsigned short getPort();
protected: 
    
void InetAddress();
};

#endif //_INETADDRESS_H