#include "Stack.h"

Stack::Stack()
{
	top = 0;
	/*int *num = new int[10];
	for (int i = 0; i < 10; i++)
	{
		num[i] = 0;
	}*/
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Stack::size() const {
  return top;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
	if (top == 0)
		return true;
	return false;
}

// `void push(int val)` - pushes an item to the stack in O(1) time
void Stack::push(int value) {
	if (top >= 10)
		return;
	num[top] = value;
	top++;
}

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
	if (top == 0)
		return -1;
	int temp;
	temp = num[top - 1];
	top--;
	return temp;
}
