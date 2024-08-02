/**
 * Project Untitled
 */


#include "producer.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using std::cout;
using std::endl;
/**
 * producer implementation
 */


/**
 * @param tQueue
 * @return void
 */
void Producer::produce(taskQueue& tQueue) {
	int cnt = 20;
	::srand(::clock());
	while(cnt--){
		int n = ::rand() % 20;
		tQueue.push(n);	
		cout << "producer number:" << n << endl;
		sleep(1);
	}
}
