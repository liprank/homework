/**
 * Project Untitled
 */


#include "TaskQueue.h"

/**
 * TaskQueue implementation
 */
TaskQueue::TaskQueue(size_t capacity)
:_queue()
,_queSize(capacity)
,_mutex()
,_notFull()
,_notEmpty()
{

}

TaskQueue::~TaskQueue(){

}

/**
 * @param task
 * @return void
 */
void TaskQueue::push(ElemType &&task) {
	unique_lock<mutex> ulock(_mutex);

	while(isFull()){
		_notFull.wait(ulock);
	}

	_queue.push(std::move(task));
	_notEmpty.notify_one();
	return;
}

/**
 * @return ElemType
 */
ElemType TaskQueue::pop() {
	unique_lock<mutex> ulock(_mutex);

	while(isEmpty()){
		_notEmpty.wait(ulock);
	}

	ElemType task = _queue.front();
	_queue.pop();
	_notFull.notify_one();
	return task;
}

bool TaskQueue::isFull() const{
	return _queSize == _queue.size();
}

bool TaskQueue::isEmpty() const{
	return 0 == _queue.size();
}

void TaskQueue::wakeup(){
	_notEmpty.notify_one();
}
