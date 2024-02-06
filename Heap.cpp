#include "Heap.h"
#include <iostream>
#include <queue>
#include <cmath>
using namespace std;




Heap::Heap(const Heap& heap) {
	m = heap.m;
	capacity = heap.capacity;
	size = heap.size;
	keys = new int[capacity];
	for (int i = 0; i < size; i++) {
		keys[i] = heap.keys[i];
	}
}
Heap::Heap(Heap&& heap) {
	m = heap.m;
	size = heap.size;
	capacity = heap.capacity;
	keys = heap.keys;
	heap.keys = nullptr;


}
Heap& Heap::operator=(const Heap& heap) {
	if (this != &heap) {

		delete[] keys;
		keys = nullptr;

		m = heap.m;
		capacity = heap.capacity;
		size = heap.size;
		keys = new int[capacity];
		for (int i = 0; i < size; i++) {
			keys[i] = heap.keys[i];
		}

	}
	return *this;
}
Heap& Heap::operator=(Heap&& heap) {
	if (this != &heap) {
		delete[] keys;
		keys = nullptr;

		m = heap.m;
		size = heap.size;
		capacity = heap.capacity;
		keys = heap.keys;
		heap.keys = nullptr;
	}
	return *this;
}
Heap::~Heap() {
	delete[] keys;
	keys = nullptr;
}

void Heap::init(int m) {
	this->m = m;
	capacity = 100;
	size = 0;
	initialized = true;
	keys = new int[capacity];
}


void Heap::add(int elem, int& steps) {
	if (size == capacity) {
		capacity += 2000;
		int* new_keys = new int[capacity];
		for (int i = 0; i < size; i++) {
			new_keys[i] = keys[i];
		}
		delete[] keys;
		keys = new_keys;
	}

	keys[size] = elem;
	size++;

	int parent, index, temp;

	index = size - 1;

	parent = (index - 1) / m;
	while (parent >= 0) {

		if (keys[index] < keys[parent]) {

			temp = keys[index];
			keys[index] = keys[parent];
			keys[parent] = temp;
			steps += 2;

			index = parent;
			parent = (index - 1) / m;

		}
		else {
			steps++;
			break;
		}
	}
}

int Heap::get() const {
	return keys[0];
}

int Heap::del(int& steps) {

	int min = keys[0];
	keys[0] = keys[size - 1];
	size--;


	int current_node, current_node_index, min_index, current_min;

	current_node = keys[0];
	current_node_index = 0;
	min_index = 0;
	current_min = current_node;

	while (1) {

		for (int i = 1; i <= m; i++) {

			if (!((m * current_node_index) + i < size)) break;

			if (keys[(m * current_node_index) + i] < current_min) {

				min_index = (m * current_node_index) + i;
				current_min = keys[min_index];

			}
			steps++;

		}


		if (min_index == current_node_index) break;


		int temp = keys[current_node_index];
		keys[current_node_index] = keys[min_index];
		keys[min_index] = temp;
		steps++;

		current_node_index = min_index;
		min_index = current_node_index;
		current_min = current_node;


	}


	return min;
}

void Heap::convertTo(int newM) {

	int temp[1000];
	int old_size = size;
	for (int i = 0; i < size; i++) {
		temp[i] = keys[i];
	}


	int steps = 0;
	size = 0;
	m = newM;
	for (int i = 0; i < old_size; i++) {
		this->add(temp[i], steps);
	}
}

void Heap::heapUnion(Heap h, int& steps) {
	if (m != h.m) {
		cout << "Razlicito m!\n";
		return;
	}
	for (int i = 0; i < h.size; i++) {
		this->add(h.keys[i], steps);
	}
}

ostream& operator<<(ostream& os, const Heap& heap) {
	if (heap.getSize() == 0) {
		return os;
	}
	queue<int> q;

	int i = 0;

	q.push(i);
	q.push(-1);

	while (q.size() > 1) {

		if (q.front() == -1) {
			cout << "\n";
			q.pop();
			q.push(-1);
			continue;
		}
		else {
			os << heap.keys[q.front()] << "(";
			if (q.front() != 0) {
				os << heap.keys[i / heap.getM()];
			}
			else {
				os << "/";
			}
			cout << ") ";
			i = q.front();
			q.pop();
		}

		for (int j = 1; j <= heap.m; j++) {

			if (!((heap.m * i) + j < heap.size)) {
				break;
			}
			else {
				q.push((heap.m * i) + j);
			}

		}
	}
	return os;
}

void Heap::destroy() {
	delete[] keys;
	initialized = false;
	keys = nullptr;
}

void Heap::deleteKey(int key) {

	int i;

	for (i = 0; i < size; i++) {
		if (keys[i] == key) {
			break;
		}
	}

	if (i == size) {
		cout << "Kljuc " << key << " ne postoji!\n";
		return;
	}

	if (i == size - 1) {
		size--;
		return;
	}



	keys[i] = keys[size - 1];
	size--;


	int parent, index, temp;

	index = i;

	parent = (index - 1) / m;
	while (parent >= 0 && keys[index] < keys[parent]) {

		temp = keys[index];
		keys[index] = keys[parent];
		keys[parent] = temp;

		index = parent;
		parent = (index - 1) / m;

	}

	int current_node, current_node_index, min_index, current_min;
	current_node = keys[i];
	current_node_index = i;
	min_index = 0;
	current_min = current_node;

	while (1) {

		for (int i = 1; i <= m; i++) {

			if (!((m * current_node_index) + i < size)) break;

			if (keys[(m * current_node_index) + i] < current_min) {

				min_index = (m * current_node_index) + i;
				current_min = keys[min_index];

			}

		}

		if (min_index == current_node_index) break;


		int temp = keys[current_node_index];
		keys[current_node_index] = keys[min_index];
		keys[min_index] = temp;

		current_node_index = min_index;
		min_index = current_node_index;
		current_min = current_node;

	}
}