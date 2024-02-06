#pragma once
#include "Heap.h"

class priorityQueue {
	
	Heap* heap;
	int delSteps;
	int insSteps;
	bool init;

public:

	priorityQueue();
	~priorityQueue();

	bool is_init() const { return init; }
	void set_m(int m) { heap->init(m); init = true; }
	bool is_empty() const { return !(heap->getSize()); }
	int front() const { return heap->get(); }
	int pop() { return heap->del(delSteps); }
	void push(int elem) {
		heap->add(elem, insSteps);
	}
	int getInsSteps() const { return insSteps; }
	int getDelSteps() const { return delSteps; }

};