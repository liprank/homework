/**
 * Project reactor
 */


#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include <vector>
#include <map>
#include <memory>
#include <sys/epoll.h>
#include <functional>
#include <mutex>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;
using std::mutex;

class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
using Functors = function<void()>;

class EventLoop {
public: 
/**
 * @param accptor
 */
EventLoop(Acceptor & accptor);

~EventLoop();
    
void loop();
    
void unloop();
    
void waitEpollFd();
    
/**
 * @param cb
 */
void setNewConnectionCallback(TcpConnectionCallback && cb);
    
/**
 * @param cb
 */
void setCloseCallback(TcpConnectionCallback && cb);
    
/**
 * @param cb
 */
void setMessageCallback(TcpConnectionCallback && cb);

private:
	int _epfd;
    vector<struct epoll_event> _evtList;
    bool _isLooping;
    Acceptor & _acceptor;
    map<int,TcpConnectionPtr> _conns;
    TcpConnectionCallback _onNewConnection;
    TcpConnectionCallback _onClose;
    TcpConnectionCallback _onMessage;	 

	int _evtfd;//用于通信的文件描述符
	vector<Functors> _pendings;//存放要执行的任务
	mutex _mutex;//对任务进行互斥访问

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
