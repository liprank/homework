/**
 * Project Untitled
 */


#ifndef _PRODUCER_H
#define _PRODUCER_H
#include "taskQueue.h"

class Producer {
public: 
Producer(){

}

~Producer(){

}

/**
 * @param tQueue
 */
void produce(taskQueue& tQueue);
};

#endif //_PRODUCER_H
