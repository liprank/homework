#include "taskQueue.h"
#include "consumer.h"
#include "producer.h"
#include <iostream>
#include <thread>

using std::thread;
using std::cout;
using std::endl;

int main(){
	Consumer c1;
	Producer p1;
	taskQueue t1(10);

	//传递引用，需要加上引用包装器
	thread ct1(&Consumer::consume,&c1,std::ref(t1));
	thread pt1(&Producer::produce,&p1,std::ref(t1));

	ct1.join();
	pt1.join();
}
