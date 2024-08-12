/**
 * Project Reactor
 */


#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <iostream>
#include <unistd.h>

using std::cerr;
using std::endl;
using std::cout;
/**
 * EventLoop implementation
 */
EventLoop::EventLoop(Acceptor & acceptor) 
:_epfd(createEpollFd())
,_acceptor(acceptor)
,_evList(1024)
,_isLooping(false)
{
	int listenfd = _acceptor.getFd();
	addEpollFd(listenfd);
}

EventLoop::~EventLoop() {
	close(_epfd);
}

/**
 * @param cb
 * @return void
 */
void EventLoop::NewConnectionCB(TcpCB && cb) {
	_onNewConnectionCB = std::move(cb);
}

/**
 * @param cb
 * @return void
 */
void EventLoop::MessageCB(TcpCB && cb) {
	_onMessageCB = std::move(cb);
}

/**
 * @param cb
 * @return void
 */
void EventLoop::CloseCB(TcpCB && cb) {
	_onCloseCB = std::move(cb);
}

/**
 * @return int
 */
int EventLoop::createEpollFd() {
	int fd = epoll_create(1);
	if(-1 == fd){
		perror("epoll_create");
		return -1;
	}
	
	return fd;
}

/**
 * @return void
 */
void EventLoop::addEpollFd(int fd) {
	struct epoll_event evt;
	evt.events = EPOLLIN;
	evt.data.fd = fd;

	int ret = epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&evt);
	if(-1 == ret){
		perror("epoll_ctl");
		return;
	}
}

/**
 * @return void
 */
void EventLoop::waitEpollFd() {
	int nready = 0;	
	do{
		nready = ::epoll_wait(_epfd,&*_evList.begin(),_evList.size(),3000);
	}while(-1 == nready && errno == EINTR);

	if(-1 == nready){
		perror("epoll_wait");
	}else if(0 == nready){
		cerr << "timeout " << endl;
	}else{
		//手动扩容
		if(nready == _evList.size()){
			_evList.resize(2*nready);
		}
		for(int i = 0; i < nready; ++i){
			int fd = _evList[i].data.fd;
			int listenfd = _acceptor.getFd();

			if(fd == listenfd){
				handleNewConnection();
			}else{
				handleMessage(fd);
			}
		}
	}
}

/**
 * @return void
 */
void EventLoop::delEpollFd(int fd) {
	struct epoll_event evt;
	evt.events = EPOLLIN;
	evt.data.fd = fd;

	int ret = epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&evt);
	if(-1 == ret){
		perror("epoll_ctl");
		return;
	}
}

/**
 * @return void
 */
void EventLoop::handleNewConnection() {
	int connfd = _acceptor.accept();
	if(-1 == connfd){
		perror("handleNewConnection");
		return;
	}
	
	//增加监听
	addEpollFd(connfd);

	shared_ptr<TcpConnection> conn(new TcpConnection(connfd));

	conn->NewConnectionCB(std::move(_onNewConnectionCB));
	conn->MessageCB(std::move(_onMessageCB));
	conn->CloseCB(std::move(_onCloseCB));	

	//更新连接map
	_conns[connfd] = conn;

	//调用新连接处理函数
	conn->NewConnectionHandle();
}

/**
 * @param fd
 * @return void
 */
void EventLoop::handleMessage(int fd) {
	auto it = _conns.find(fd);
	if(it != _conns.end()){
		bool flag = it->second->isClosed();		
		if(flag){
			//断开连接
			it->second->CloseHandle();
			delEpollFd(fd);
			_conns.erase(it);
		}else{
			it->second->MessageHandle();
		}
	}else{
		cout << "连接不存在" << endl;
		return;
	}
}

void EventLoop::loop(){
	_isLooping = true;
	while(_isLooping){
		waitEpollFd();
	}
}

void EventLoop::unloop(){
	_isLooping = false;
}
