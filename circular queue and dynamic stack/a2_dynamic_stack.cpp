// Sunghoon Ahn 20615061
#include <iostream>
#include "a2_dynamic_stack.hpp"

using namespace std;

typedef DynamicStack::StackItem StackItem;  // for simplicity
const StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
	items_ = new StackItem[16];
	capacity_ = 16;
	init_capacity_ = 16;
	size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity)
{
	items_ = new StackItem[capacity];
	capacity_ = capacity;
	init_capacity_ = capacity;
	size_ = 0;
}

DynamicStack::~DynamicStack()
{
	delete [] items_;
	items_ = NULL;
	size_ = 0;
}

bool DynamicStack::empty() const
{
	return (size_ == 0);
}

int DynamicStack::size() const
{
	return size_;
}

void DynamicStack::push(StackItem value)
{
	if(size_ == capacity_) {
		int newCapacity = capacity_ * 2;
		StackItem *other = new StackItem[newCapacity];
		for(int i=0; i<size_; i++)
			other[i] = items_[i];
		other[size_] = value;
		capacity_ = newCapacity;
		delete [] items_;
		items_ = other;
		size_++;
	}
	else {
		items_[size_] = value;
		size_++;
	}
}

StackItem DynamicStack::pop()
{
	if(empty())
		return EMPTY_STACK;
	else {
		StackItem value = items_[size_-1];
		if(size_ <= (capacity_/4) && (capacity_/2) >= init_capacity_) {
			int newCapacity = capacity_ / 2;
			StackItem *other = new StackItem[newCapacity];
			for(int i=0; i<size_-1; i++)
				other[i] = items_[i];
			capacity_ = newCapacity;
			delete [] items_;
			items_ = other;
		}
		size_--;
		return value;
	}
}

StackItem DynamicStack::peek() const
{
	if(size_ == 0)
		return EMPTY_STACK;
	else
		return items_[size_-1];
}

void DynamicStack::print() const
{
	for(int i=size_-1; i>=0; i--)
		cout << items_[i] << endl;
}
