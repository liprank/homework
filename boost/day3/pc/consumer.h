/**
 * Project Untitled
 */

#ifndef _CONSUMER_H
#define _CONSUMER_H
#include "taskQueue.h"
class Consumer {
public: 
Consumer();
~Consumer();

/**
 * @param tQueue
 */
void consume(taskQueue& tQueue);
};

#endif //_CONSUMER_H
