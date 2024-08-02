/**
 * Project Reactor
 */


#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H

class TcpConnection {
public: 
    
/**
 * @param fd
 */
void TcpConnection(int fd);
    
void ~TcpConnection();
private: 
    InetAddress _localAddr;
    InetAddress _peerAddr;
    Socket _sock;
    SocketIO _sockIO;
    
/**
 * @param const string &
 */
int send(void const string &);
    
string receive();
    
InetAddress getlocalAddr();
    
InetAddress getpeerAddr();
};

#endif //_TCPCONNECTION_H