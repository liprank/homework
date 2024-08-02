/**
 * Project Reactor
 */


#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H

class Acceptor {
public: 
    Socket _sock;
    InetAddress _addr;
    
void accept();
    
void ready();
    
/**
 * @param ip
 * @param port
 */
void Acceptor(const string & ip, unsigned short port);
    
void setReuseAddr();
    
void setReusePort();
protected: 
    
void Acceptor();
private: 
    
void bind();
    
void listen();
};

#endif //_ACCEPTOR_H