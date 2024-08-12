/**
 * Project Reactor
 */


#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

using std::string;
using std::function;
using std::shared_ptr;

class TcpConnection 
: public std::enable_shared_from_this<TcpConnection>
{
	using TcpCB = function<void(const shared_ptr<TcpConnection> &)>;
public: 
/**
 * @param fd
 */
explicit TcpConnection(int fd);
    
~TcpConnection();

/**
 * @param const string &
 */
void send(const string &);
    
string receive();

string toString();

//三个回调函数的注册
void NewConnectionCB(TcpCB && cb);

void MessageCB(TcpCB && cb);

void CloseCB(TcpCB && cb);

//三个回调函数的执行
void NewConnectionHandle();

void MessageHandle();

void CloseHandle();

bool isClosed() const;
private: 
    InetAddress _localAddr;
    InetAddress _peerAddr;
    Socket _sock;
    SocketIO _sockIO;
	TcpCB _onNewConnectionCB;
	TcpCB _onMessageCB;
	TcpCB _onCloseCB;
  
InetAddress getlocalAddr();
    
InetAddress getpeerAddr();

};

#endif //_TCPCONNECTION_H
