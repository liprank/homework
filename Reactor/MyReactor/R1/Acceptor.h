/**
 * Project Reactor
 */


#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H
#include "Socket.h" 
#include "InetAddress.h"

class Acceptor {
public: 
    Socket _sock;
    InetAddress _addr;
    
int accept();
    
void ready();
    
/**
 * @param ip
 * @param port
 */
Acceptor(const string & ip, unsigned short port);

~Acceptor();
    
void setReuseAddr();
    
void setReusePort();
private: 
    
void bind();
    
void listen();
};

#endif //_ACCEPTOR_H
