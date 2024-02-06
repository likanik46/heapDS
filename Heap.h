#pragma once
#include <iostream>
using namespace std;

class Heap {

	bool initialized = false;
	int m;
	int capacity;
	int size;
	int* keys = nullptr;


public:


	Heap() = default;
	Heap(const Heap& heap);
	Heap(Heap&& heap);
	Heap& operator=(const Heap& heap);
	Heap& operator=(Heap&& heap);
	~Heap();



	int getSize() const { return size; }
	int getCapacity() const { return capacity; }
	int getM() const { return m; }
	bool getInit() const { return initialized; }

	void init(int m);
	void add(int elem, int& steps);
	int get() const;
	int del(int& steps);
	void convertTo(int newM);
	void heapUnion(Heap h, int& steps);
	friend ostream& operator<<(ostream& os, const Heap& heap);
	void destroy();
	void deleteKey(int key);





	



};