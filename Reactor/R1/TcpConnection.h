/**
 * Project reactor
 */


#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"

class TcpConnection {
public: 
    
/**
 * @param fd
 */
explicit TcpConnection(int fd);
    
~TcpConnection();
    
/**
 * @param msg
 */
void send(const string & msg);
    
string receive();

//方便调试
string toString();
private: 
    InetAddress _localAddr;
    InetAddress _peerAddr;
    SocketIO _sockIO;
    Socket _sock;
   
private:
InetAddress getLocalAddr();
    
InetAddress getPeerAddr();
};

#endif //_TCPCONNECTION_H
