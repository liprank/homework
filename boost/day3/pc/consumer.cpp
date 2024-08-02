/**
 * Project Untitled
 */


#include "consumer.h"
#include "taskQueue.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;
/**
 * consumer implementation
 */

Consumer::Consumer(){

}

Consumer::~Consumer(){

}

/**
 * @param tQueue
 * @return void
 */
void Consumer::consume(taskQueue& tQueue) {
	int cnt = 20;
	while(cnt--){
		int n = tQueue.pop();
		cout << "consumer:" << n << endl;
		sleep(1);
	}
}
