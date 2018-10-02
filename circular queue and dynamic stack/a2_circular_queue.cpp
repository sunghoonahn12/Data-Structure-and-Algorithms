// Sunghoon Ahn 20615061
#include <iostream>
#include "a2_circular_queue.hpp"

using namespace std;

typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
	items_ = new QueueItem[16];
	capacity_ = 16;
	size_ = 0;
	head_ = 0;
	tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
	items_ = new QueueItem[capacity];
	capacity_ = capacity;
	size_ = 0;
	head_ = 0;
	tail_ = 0;
}

CircularQueue::~CircularQueue()
{
	delete [] items_;
	items_ = NULL;
	size_ = 0;
}

bool CircularQueue::empty() const
{
	return size_ == 0;
}

bool CircularQueue::full() const
{
	return size_ >= capacity_;
}

int CircularQueue::size() const
{
	return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
	if(full())
		return false;
	else {
		items_[tail_++] = value;
		tail_ %= capacity_;
		size_++;
		return true;
	}
}

QueueItem CircularQueue::dequeue()
{
	if(empty())
		return EMPTY_QUEUE;
	else {
		int value = items_[head_];
		items_[head_] = 0;
		head_ = (head_ + 1) % capacity_;
		size_--;
		return value;
	}
}

QueueItem CircularQueue::peek() const
{
	if(size_ == 0)
		return EMPTY_QUEUE;
	else
		return items_[head_];
}

void CircularQueue::print() const
{
	for(int i=head_; i<size_; i++) {
		cout << items_[i] << endl;
	}
}
