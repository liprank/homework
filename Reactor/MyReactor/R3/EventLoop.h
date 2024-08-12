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

using std::function;
using std::shared_ptr;
using std::vector;
using std::map;

//前向声明，避免循环引用问题
class TcpConnection;
class Acceptor;

using TcpCB = function<void(const shared_ptr<TcpConnection>)>;

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

private: 
    int _epfd;
    Acceptor &_acceptor;
    vector<epoll_event> _evList;
    map<int,shared_ptr<TcpConnection>> _conns;
    TcpCB _onNewConnectionCB;
    TcpCB _onMessageCB;
    TcpCB _onCloseCB;
	bool _isLooping;
    
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
