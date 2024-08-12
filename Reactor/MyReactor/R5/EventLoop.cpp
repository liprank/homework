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
using std::lock_guard;
/**
 * EventLoop implementation
 */
EventLoop::EventLoop(Acceptor & acceptor) 
:_epfd(createEpollFd())
,_acceptor(acceptor)
,_evList(1024)
,_isLooping(false)
,_evtfd(createEventFd())
,_mutex()
{
	int listenfd = _acceptor.getFd();
	addEpollFd(listenfd);

	//将用于通信的文件描述符进行监听
	addEpollFd(_evtfd);
}

EventLoop::~EventLoop() {
	close(_epfd);
	close(_evtfd);
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
			}else if(fd == _evtfd){
				//用于进程间通信的文件描述符
				handleRead();
				//做任务
				doPengingFunctors();
			}
			else{
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

int EventLoop::createEventFd(){
	int evtfd = ::epoll_create(1);
	if(evtfd < 0){
		perror("createEpollFd");	
		return -1;
	}
	return evtfd;
}

void EventLoop::runLoop(Functor &&cb){
	{
		lock_guard<mutex> lguard(_mutex);
		_pendings.push_back(std::move(cb));
	}
	handleWrite();
}

void EventLoop::handleWrite(){
	uint64_t one = 1;
	//唤醒进程间通信文件描述符
	ssize_t ret = write(_evtfd,&one,sizeof(uint64_t));
	if(ret != sizeof(uint64_t)){
		perror("wake up");
		return;
	}
}


//唤醒进程间通信文件描述符
void EventLoop::handleRead(){
	uint64_t one = 1;
	ssize_t ret = read(_evtfd,&one,sizeof(uint64_t));
	if(ret != sizeof(uint64_t)){
		perror("handleRead");
		return;
	}
}

void EventLoop::doPengingFunctors(){
	vector<Functor> temp;
	{
		lock_guard<mutex> lguard(_mutex);
		//取出等待的任务队列，并交换为空
		temp.swap(_pendings);
	}

	for(auto &cb : temp){
		//执行任务，任务中有TcpConnection的send函数和msg,即发送信息
		cb();
	}
}
