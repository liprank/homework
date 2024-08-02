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

class EventLoop;

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
explicit TcpConnection(int fd,EventLoop *loop);
    
~TcpConnection();
    
/**
 * @param msg
 */
void send(const string & msg);

void sendInLoop(const string & msg);
    
string receive();

//方便调试
string toString();

//查看连接是否断开
bool isClosed();
private: 
	EventLoop *_loop;
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


};

#endif //_TCPCONNECTION_H
