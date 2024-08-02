/**
 * Project Untitled
 */


#include "TaskQueue.h"
#include <iostream>

using std::queue;
using std::condition_variable;
using std::mutex;
using std::unique_lock;


//避免循环引用问题

/**
 * TaskQueue implementation
 */


/**
 * @param ptask
 * @return void
 */

TaskQueue::TaskQueue(size_t capacity)
:_capacity(capacity)
,_que()
,_mutex()
,_notfull()
,_notempty()
,_flag(true)
{

}

bool TaskQueue::isempty()const{
	return 0 == _que.size();
}

bool TaskQueue::isfull()const{
	return _capacity == _que.size(); 
}

void TaskQueue::wakeup(){
	_notempty.notify_one();
}

TaskQueue::~TaskQueue(){

}

void TaskQueue::push(ElemType ptask) {
	unique_lock<mutex> ul(_mutex);	

	while(isfull()){
		_notfull.wait(ul);
	}

	_que.push(ptask);
	_notempty.notify_one();
    return;
}

/**
 * @return ElemType
 */
ElemType TaskQueue::pop() {
	unique_lock<mutex> ul(_mutex);
	
	/* bool flag = true; */
	while(isempty()){
		_notempty.wait(ul);
	}

	//判断empty不为false
	ElemType temp = _que.front();
	_que.pop();
	_notfull.notify_one();
	return temp;
}
