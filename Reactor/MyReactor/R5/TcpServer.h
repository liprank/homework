/**
 * Project Reactor
 */


#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include "Acceptor.h"
#include "EventLoop.h"

class TcpServer {
public: 
    Acceptor _acceptor;
    EventLoop _loop;
    
/**
 * @param ip
 * @param port
 */
TcpServer(const string & ip, unsigned short port);
    
~TcpServer();
    
void start();
    
void stop();
    
void setAllCB(TcpCB &&cb1,TcpCB &&cb2,TcpCB &&cb3);
};

#endif //_TCPSERVER_H
