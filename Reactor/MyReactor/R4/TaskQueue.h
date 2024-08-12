/**
 * Project Untitled
 */

#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

using std::function;
using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

using ElemType = function<void()>;

class TaskQueue {
public: 
/**
 * @param capacity
 */
TaskQueue(size_t capacity);

~TaskQueue();

/**
 * @param ptask
 */
void push(ElemType &&task);
    
ElemType pop();

bool isEmpty() const;

bool isFull() const;

//TIP:防止线程在isempty中阻塞，导致无法终止，加入空任务并且唤醒
void wakeup();
private: 
    queue<ElemType> _queue;
	size_t _queSize;	
	mutex _mutex;
	condition_variable _notFull;
	condition_variable _notEmpty;
};

#endif //_TASKQUEUE_H
