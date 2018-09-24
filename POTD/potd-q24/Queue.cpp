#include "Queue.h"

Queue::Queue() 
{
	size_ = 0;
	head_ = NULL;
	tail = NULL; 
	curr = NULL;
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const {
	return size_;
//  return 0;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
	if (size_ == 0)
		return true;
	return false;
//  return true;
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value) {
	if (head_ == NULL)
	{
		head_ = new Node();
		head_->data = value;
		head_->next = NULL;
		tail = head_;
		//curr = head_;
		size_++;
	}
	else
	{
		Node *temp = new Node();
		temp->data = value;
		temp->next = NULL;
		tail->next = temp;
		curr = tail;
		tail = temp;
		size_++;
	}
}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
	if (size_ == 0)
		return -1;
	else if (size_ == 1)
	{
		int v = head_->data;
		delete head_;
		head_ = NULL;
		size_--;
		return v;
	}
	else
	{
		int v = head_->data;
		Node *temp = head_->next;
		delete head_;
		head_ = NULL;
		head_ = temp;
		size_--;
		return v;
	}
}
