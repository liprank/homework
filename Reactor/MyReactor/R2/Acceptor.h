/**
 * Project Reactor
 */


#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H
#include "Socket.h" 
#include "InetAddress.h"

class Acceptor {
public: 
/**
 * @param ip
 * @param port
 */
Acceptor(const string & ip, unsigned short port);

~Acceptor();
    
int accept();
    
void ready();

int getFd();
private: 
    Socket _sock;
    InetAddress _addr;

private:
void bind();
    
void listen();

void setReuseAddr();
    
void setReusePort();
};

#endif //_ACCEPTOR_H
