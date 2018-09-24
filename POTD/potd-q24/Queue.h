#ifndef _QUEUE_H
#define _QUEUE_H

#include <cstddef>

struct Node
{
	Node *next;
	int data;
};

class Queue {
    public:
	Queue();
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
	int size_;
	Node *head_;
	Node *tail;
	Node *curr;
};

#endif
