/**
 * Project reactor
 */


#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"

#include <memory> 
#include <functional>

using std::shared_ptr;
using std::function;

class TcpConnection 
: public std::enable_shared_from_this<TcpConnection>
{
	using TcpConnectionPtr = shared_ptr<TcpConnection>;
	using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
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

	TcpConnectionCallback _onNewConnection;
	TcpConnectionCallback _onMessage;
	TcpConnectionCallback _onClose;
   
private:
InetAddress getLocalAddr();
    
InetAddress getPeerAddr();

/**
 * @param cb
 */
void setNewConnectionCallback(const TcpConnectionCallback & cb);

/**
 * @param cb
 */
void setCloseCallback(const TcpConnectionCallback & cb);

/**
 * @param cb
 */
void setMessageCallback(const TcpConnectionCallback & cb);

void handleNewConnectionCallback();

void handleCloseCallback();

void handleMessageCallback();

bool isClosed();
};

#endif //_TCPCONNECTION_H
