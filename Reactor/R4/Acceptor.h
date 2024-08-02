/**
 * Project reactor
 */


#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H

#include "Socket.h"
#include "InetAddress.h"
#include <string>

class Acceptor {
public: 
    
/**
 * @param ip
 * @param port
 */
Acceptor(const string & ip, unsigned short port);
    
~Acceptor();
    
void ready();
    
int accept();

int getFd() const;
private: 
    Socket _sock;
    InetAddress _addr;
    
void setReuseAddr();
    
void setReusePort();
    
void bind();
    
void listen();
};

#endif //_ACCEPTOR_H
