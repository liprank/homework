/**
 * Project reactor
 */

#include "TcpConnection.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include <unistd.h>
#include <iostream>
#include <sys/eventfd.h>

using std::cerr;
using std::cout;
using std::endl;

/**
 * EventLoop implementation
 */


/**
 * @param accptor
 */
EventLoop::EventLoop(Acceptor & accptor) 
:_epfd(createEpollFd())
,_evtList(1024)
,_isLooping(false)
,_acceptor(accptor)
,_evtfd(createEventFd())
{
	int listenfd = _acceptor.getFd();
	addEpollReadFd(listenfd);
	addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop(){
	close(_epfd);
	close(_evtfd);
}

/**
 * @return void
 */
void EventLoop::loop() {
	_isLooping = true;
	while(_isLooping){
		waitEpollFd();
	}
}

/**
 * @return void
 */
void EventLoop::unloop() {
	_isLooping = false;
}

/**
 * @return void
 */
void EventLoop::waitEpollFd() {
	int nready = 0;
	nready = ::epoll_wait(_epfd,&*_evtList.begin(),_evtList.size(),300);

	if(-1 == nready){
		cerr << "-1 == nready" << endl;
		return;
	}else if(0 == nready){
		cout << "epoll_wait timeout" << endl;
	}else{
		if(nready == (int)_evtList.size()){
			_evtList.resize(2 * nready);
		}

		for(int idx = 0;idx < nready; ++idx){
			//处理消息
			int fd = _evtList[idx].data.fd;
			//处理连接
			int listenfd = _acceptor.getFd();

			if(fd == listenfd){
				handleNewConnection();
			}else if(fd == _evtfd){
				handleRead();
				doPengdingFunctors();
			}else{
				handleMessage(fd);
			}
		}
	}
}

/**
 * @return void
 */
void EventLoop::handleNewConnection() {
	int connfd = _acceptor.accept();
	if(connfd < 0){
		perror("handleNewConnection");
		return;
	}

	addEpollReadFd(connfd);

	TcpConnectionPtr con(new TcpConnection(connfd,this));

	con->setNewConnectionCallback(_onNewConnection);
	con->setMessageCallback(_onMessage);
	con->setCloseCallback(_onClose);

	_conns[connfd] = con;
	con->handleNewConnectionCallback();
}

/**
 * @param fd
 * @return void
 */
void EventLoop::handleMessage(int fd) {
	auto it = _conns.find(fd);
	if(it != _conns.end()){
		string msg = it->second->receive();
		cout << "recv msg from client: " << msg << endl;
		//发送数据
		//it->second->send(msg);
	}else{
		cout << "wrong connection" << endl;
		return;
	}
	
}

/**
 * @return int
 */
int EventLoop::createEpollFd() {
	int fd = ::epoll_create(1);
	if(fd < 0){
		perror("createEpollFd");
		return -1;
	}
	return fd;
}

/**
 * @param fd
 * @return void
 */
void EventLoop::addEpollReadFd(int fd) {
	struct epoll_event evt;
	evt.events = EPOLLIN;
	evt.data.fd = fd;

	int ret = ::epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&evt);
	if(ret < 0){
		perror("addEpollReadFd");
		return;
	}
}

/**
 * @param fd
 * @return void
 */
void EventLoop::delEpollReadFd(int fd) {
	struct epoll_event evt;
	evt.events = EPOLLIN;
	evt.data.fd = fd;

	int ret = ::epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&evt);
	if(ret < 0){
		perror("delEpollReadFd");
		return;
	}
}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onNewConnection = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessage = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onClose = std::move(cb);
}

void EventLoop::doPengdingFunctors(){
	vector<Functors> tmp;
	{
		lock_guard<mutex> lg(_mutex);
		tmp.swap(_pendings);
	}

	for(auto &cb : tmp){
		cb();
	}
}

void EventLoop::runInLoop(Functors &&cb){
	{
		lock_guard<mutex> lg(_mutex);
		_pendings.push_back(std::move(cb));
	}

	wakeup();
}
