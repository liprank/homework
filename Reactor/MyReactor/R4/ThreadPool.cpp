/**
 * Project Untitled
 */

#include "ThreadPool.h"
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
	for(int idx = 0; idx < _threadNum; ++idx){
		_threads.push_back(thread(&ThreadPool::doTask,this));
	}
    return;
}

/**
 * @return void
 */
void ThreadPool::stop() {
	while(!_taskQue.isEmpty()){
		//TIP:避免主程序运行过快
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

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
void ThreadPool::addTask(Task &&task) {
	if(task){
		_taskQue.push(std::move(task));
	}
}

/**
 * @return Task*
 */
Task ThreadPool::getTask() {
	return _taskQue.pop();
}

/**
 * @return void
 */
void ThreadPool::doTask() {
	while(!_isExit){
		Task taskCB = getTask();
		if(taskCB){
			taskCB();
		}else{
			cout << "task is nullptr" << endl;
		}
	}
}
