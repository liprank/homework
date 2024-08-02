/**
 * Project reactor
 */


#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include <vector>
#include <map>
#include <memory>
#include <sys/epoll.h>

using std::vector;
using std::map;
using std::shared_ptr;

class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
class EventLoop {
public: 
    int _epfd;
    vector<struct epoll_event> _evtList;
    bool _isLooping;
    Acceptor & _acceptor;
    map<int,TcpConnectionPtr> _conns;
    
/**
 * @param accptor
 */
EventLoop(Acceptor & accptor);

~EventLoop();
    
void loop();
    
void unloop();
    
void waitEpollFd();
    
void handleNewConnection();
    
/**
 * @param fd
 */
void handleMessage(int fd);
    
int createEpollFd();
    
/**
 * @param fd
 */
void addEpollReadFd(int fd);
    
/**
 * @param fd
 */
void delEpollReadFd(int fd);
};

#endif //_EVENTLOOP_H
