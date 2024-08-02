/**
 * Project productor and consumer 
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

class taskQueue {
public: 
    
/**
 * @param capacity
 */
taskQueue(size_t capacity);
    
~taskQueue();
    
/**
 * @param value
 */
void push(const int& value);
    
int pop();
    
bool isfull();
    
bool isempty();
private: 
    size_t _capacity;
    queue<int> _queue;
    mutex _mutex;
    condition_variable _notempty;
    condition_variable _notfull;
};

#endif //_TASKQUEUE_H
