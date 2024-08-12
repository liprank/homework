/**
 * Project Untitled
 */


#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "TaskQueue.h"
#include <functional>
#include <thread>

using std::function;
using std::vector;
using std::thread;

using Task = function<void()>;
class ThreadPool {
public: 
    
/**
 * @param threadNum
 * @param queSize
 */
ThreadPool(size_t threadNum, size_t queSize);
    
~ThreadPool();
    
void start();
    
void stop();
    
/**
 * @param ptask Task*
 */
void addTask(Task &&task);
    
Task getTask();
private: 
    size_t _threadNum;
    vector<thread> _threads;
    size_t _queSize;
    TaskQueue _taskQue;
    bool _isExit;
    
void doTask();
};

#endif //_THREADPOOL_H
