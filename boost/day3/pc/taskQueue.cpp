/**
 * Project producer and consumer 
 */
#include "taskQueue.h"
using std::unique_lock;

/**
 * @param capacity
 */
taskQueue::taskQueue(size_t capacity)
:_capacity(capacity)
,_queue()
,_mutex()
,_notempty()
,_notfull()
{

}
    
taskQueue::~taskQueue(){

}
    
/**
 * @param value
 */
void taskQueue::push(const int& value){
	//0.获取锁
	unique_lock<mutex> ul(_mutex);

	//1.如果为满
	while(isfull()){//使用while而不是if，避免wait倒置的虚假唤醒问题
		//阻塞该线程直到_notfull条件被满足
		
		//上半部：释放锁、睡眠
		_notfull.wait(ul);
		//下半部：被唤醒、抢占锁、返回
	}

	//2.如果非满,生产数据
	_queue.push(value);

	//3.通知消费者
	_notempty.notify_one();
}
    
int taskQueue::pop(){
	unique_lock<mutex> ul(_mutex);	

	//1.如果为空
	while(isempty()){
		//阻塞该线程直到_notempty条件被满足
		_notempty.wait(ul);
	}

	//2.如果非空,弹出数据
	int temp = _queue.front();
	_queue.pop();

	//3.通知生产者
	_notfull.notify_one();
	return temp;
}
    
bool taskQueue::isfull(){
	return _queue.size() == _capacity;
}
    
bool taskQueue::isempty(){
	return 0 == _queue.size();
}
