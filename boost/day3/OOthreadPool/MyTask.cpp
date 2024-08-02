/**
 * Project Untitled
 */


#include "MyTask.h"
#include "ThreadPool.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;
/**
 * MyTask implementation
 */


/**
 * @return void
 */

std::mutex out_mutex;
void MyTask::process() {
	//MyTask到底执行什么任务
        //(需要根据具体的业务逻辑添加任务)
        ::srand(::clock());//种随机种子
        int number = ::rand() % 100;//产生随机数
		out_mutex.lock();
        cout << "MyTask number = " << number << endl;
		out_mutex.unlock();
}

//1、任务添加了20次，但是并没有进行20次
//2、没有退出的问题
void test(){
	//只要遇到new，就可以使用智能指针替换
	unique_ptr<Task> ptask(new MyTask());
	ThreadPool pool(4,10);
	pool.start();

	int cnt = 20;
	while(cnt--){
		pool.addTask(ptask.get());
	}

	pool.stop();
}

int main(){
	test();
	return 0;
}

