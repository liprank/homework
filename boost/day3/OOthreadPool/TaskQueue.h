/**
 * Project Untitled
 */


#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

using std::queue;
using std::mutex;
using std::condition_variable;

class Task;
using ElemType = Task*;

class ThreadPool;

class TaskQueue {
public: 
//问题二
//方案一:设置友元
/* friend */
/* ThreadPool::stop(); */
TaskQueue(size_t capacity);
~TaskQueue();

/**
 * @param ptask
 */
void push(ElemType ptask);
ElemType pop();

bool isempty() const;
bool isfull() const;
void wakeup();

private: 
	size_t _capacity;
    queue<ElemType> _que;
	mutex _mutex;
	condition_variable _notfull;
	condition_variable _notempty;
	bool _flag;
};

#endif //_TASKQUEUE_H
