/**
 * Project reactor
 */


#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include "EventLoop.h"
#include "Acceptor.h"

using std::string;
class TcpServer {
public: 
    
/**
 * @param ip
 * @param port
 */
TcpServer(const string & ip, unsigned short port);
~TcpServer();
    
void start();
    
void stop();
    
/**
 * @param cb1
 * @param cb2
 * @param cb3
 */
void setAllCallback(TcpConnectionCallback && cb1, TcpConnectionCallback && cb2, TcpConnectionCallback && cb3);
private: 
    Acceptor _acceptor;
    EventLoop _loop;
};

#endif //_TCPSERVER_H
