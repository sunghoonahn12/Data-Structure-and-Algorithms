// Sunghoon Ahn 20615061

#include "a3_priority_queue.hpp"
#include <stdio.h>
#include <iostream>

PriorityQueue::PriorityQueue(unsigned int capacity){
	capacity_ = capacity;						// initialize capacity to function input
	heap_ = new DataType[capacity_ + 1];		// initialize array to size of capacity + 1
	size_ = 0;									// initialize size to 0
}

PriorityQueue::~PriorityQueue(){
	delete [] heap_;							// delete array
	heap_ = NULL;								// set pointer to NULL
}

unsigned int PriorityQueue::size() const{
	return size_;								// return size
}

bool PriorityQueue::empty() const{
	return size_ == 0;							// return whether or not size is 0
}

bool PriorityQueue::full() const{
	return size_ == capacity_;					// return whether or not size is equal to capacity
}

void PriorityQueue::print() const{
	for (int i = 1; i <= size_; i++)			// print each item in queue in breadth first approach
		std::cout << "[" << heap_[i] <<"] ";
	std::cout << std::endl << std::endl;
}

PriorityQueue::DataType PriorityQueue::max() const{
	return heap_[1];							// return max value of heap which should be the root
}


bool PriorityQueue::enqueue(DataType val){
	if (full())									// check if queue is already full
		return false;

	int curNode = size_ + 1;					// create curNode index at where new val should be (before floating new val up heap)

	if (empty())
		heap_[1] = val;							// special case for enqueue into an empty queue
	else
	{
		while (val > heap_[curNode / 2] && curNode != 1)	// search for correct location to place new val in max heap
		{
			heap_[curNode] = heap_[curNode / 2];
			curNode = curNode / 2;
		}
		heap_[curNode] = val;
	}

	size_++;									// increment size
	return true;
}

bool PriorityQueue::dequeue(){
	if (empty())								// check if queue is empty
		return false;

	int curNode = 1;

	heap_[1] = heap_[size_];					// move last value in heap to root

	while (2*curNode + 1 <= size_)				// move new root to proper location in heap
	{
		bool right = 0;
		if (heap_[2*curNode] < heap_[2*curNode + 1])	// find larger chile (right or left)
			right = 1;
		if (heap_[curNode] < heap_[2*curNode + right])	// check if children are both smaller
		{
			int temp = heap_[curNode];
			heap_[curNode] = heap_[2*curNode + right];
			heap_[2*curNode + right] = temp;
		}
		curNode = 2*curNode + right;
	}

	if (2*curNode <= size_)						// special case for if moved node was only child
	{
		heap_[curNode] = heap_[2*curNode];
	}

	size_--;									// decrememnt size
	return true;
}
