/**
 * Project Reactor
 */


#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include <functional>
#include <memory>
#include <vector>
#include <map>
#include <sys/epoll.h>
#include <mutex>

using std::function;
using std::shared_ptr;
using std::vector;
using std::map;
using std::mutex;
using std::unique_lock;

//前向声明，避免循环引用问题
class TcpConnection;
class Acceptor;

using TcpCB = function<void(const shared_ptr<TcpConnection>)>;
using Functor = function<void()>;

class EventLoop {
public: 
    
EventLoop(Acceptor &acceptor);
    
~EventLoop();
    
/**
 * @param cb
 */
void NewConnectionCB(TcpCB && cb);
    
/**
 * @param cb
 */
void MessageCB(TcpCB && cb);
    
/**
 * @param cb
 */
void CloseCB(TcpCB && cb);

void loop();

void unloop();

//进程间通信
int createEventFd();
void handleRead();
void handleWrite();
void doPengingFunctors();

void runLoop(Functor && cb);//接收绑定Tcpconnection的send函数和接收msg的函数

private: 
    int _epfd;
    Acceptor &_acceptor;
    vector<epoll_event> _evList;
    map<int,shared_ptr<TcpConnection>> _conns;
    TcpCB _onNewConnectionCB;
    TcpCB _onMessageCB;
    TcpCB _onCloseCB;
	bool _isLooping;

	//用于进程间通信
	int _evtfd;
	vector<Functor> _pendings;
	mutex _mutex;
    
int createEpollFd();
    
void addEpollFd(int fd);
    
void waitEpollFd();
    
void delEpollFd(int fd);
    
void handleNewConnection();
    
/**
 * @param fd
 */
void handleMessage(int fd);

};

#endif //_EVENTLOOP_H
