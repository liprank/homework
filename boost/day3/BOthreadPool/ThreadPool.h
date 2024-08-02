/**
 * Project Untitled
 */


#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "TaskQueue.h"
#include <vector>
#include <thread>
#include <functional>

using std::vector;
using std::thread;
using std::function;

//线程池所需要执行的任务
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
//bind生成一个临时的函数对象，所以需要右值引用
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
