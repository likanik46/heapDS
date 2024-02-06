#include "PriorityQueue.h"

priorityQueue::priorityQueue() {
	heap = new Heap;
	init = false;
	delSteps = 0;
	insSteps = 0;
}




priorityQueue::~priorityQueue() {
	heap->destroy();
	delete heap;
}


