/**
 * Project Reactor
 */


#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include <string>

using std::string;
class TcpConnection {
public: 
    
/**
 * @param fd
 */
TcpConnection(int fd);
    
~TcpConnection();

/**
 * @param const string &
 */
void send(const string &);
    
string receive();

string toString();

private: 
    InetAddress _localAddr;
    InetAddress _peerAddr;
    Socket _sock;
    SocketIO _sockIO;
  
InetAddress getlocalAddr();
    
InetAddress getpeerAddr();
};

#endif //_TCPCONNECTION_H
