/**
 * Project Untitled
 */


#include "ThreadPool.h"
#include "Task.h"
#include <iostream>

using std::cout;
using std::endl;

/**
 * ThreadPool implementation
 */


/**
 * @param threadNum
 * @param queSize
 */
ThreadPool::ThreadPool(size_t threadNum, size_t queSize) 
:_threadNum(threadNum)
,_threads()
,_queSize(queSize)
,_taskQue(_queSize)
,_isExit(false)
{

}

ThreadPool::~ThreadPool() {

}

/**
 * @return void
 */
void ThreadPool::start() {
	for(size_t idx = 0; idx != _threadNum; ++idx){
		//创建的线程
		/* thread th(&ThreadPool::doTask,this); */	
		/* _threads.push_back(std::move(th)); */
		//thread没有拷贝构造函数，所以不能传递左值，只能传递右值（临时变量）	
		_threads.push_back(thread(&ThreadPool::doTask,this));
	}
}

/**
 * @return void
 */
void ThreadPool::stop() {
	//问题一
	//主线程可能执行太快
	while(!_taskQue.isempty()){
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	/* _taskQue.wakeup(); */
	_isExit = true;
	for(int i = 0; i < _threadNum; ++i){
		_taskQue.push(nullptr);
		_taskQue.wakeup();
	}

	for(auto &th : _threads){
		th.join();
	}
}

/**
 * @param ptask Task*
 * @return void
 */
void ThreadPool::addTask(Task* ptask) {
	if(ptask){
		_taskQue.push(ptask);
	}
}

/**
 * @return Task*
 */
Task* ThreadPool::getTask() {
    return _taskQue.pop();
}

/**
 * @return void
 */
void ThreadPool::doTask() {
	/* while(!_taskQue.isempty()){ */
	while(!_isExit){

		//问题二
		//子线程在gettask获取完任务之后，任务队列就会为空，那么子线程就会继续向下执行任务，也就是调用process函数，但是主线程在执行stop函数，发现任务队列为空，那么主线程也会继续向下执行，
		//如果主线程执行的速率比较快，也就是子线程执行process的速率比较慢，主线程将isexit设为true,process之后就不会再进入到while循环，那么主线程就可以将子线程回收,那么整个程序就可以退出
		//如果主线程执行的速率比较慢，那么就有可能子线程在执行完process之后又进入while循环之中，陷入睡眠，主线程就无法结束子线程
		//
		//方案一：唤醒子线程notify_all
		Task* ptask = getTask();
		if(ptask){
			ptask->process();//多态
		}else{
			cout << "ptask == nullptr" << endl;
		}
	}
}
