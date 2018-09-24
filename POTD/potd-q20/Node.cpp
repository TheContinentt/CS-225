#include "Node.h"

using namespace std;

Node *listUnion(Node *first, Node *second) {
  // your code here
	if (first == NULL && second == NULL)
		return NULL;
	else if (first == NULL && second != NULL)
		return second;
	else if (first != NULL && second == NULL)
		return first;
 	Node *temp = second;
	Node *t = first;
	Node *pv;
	Node *store;
	int flag = 0;
	while (temp != NULL)
	{
		store = temp->next_;
		while (t != NULL)
		{
			if (t->data_ == temp->data_)
			{
				flag = 1;
				//temp = temp->next;
				//t = first;
				break;
			}
			else
			{
				pv = t;
				t = t->next_;
			}
		}
		if (flag == 0)
		{
			pv->next_ = temp;
			temp->next_ = NULL;
		}
		flag = 0;
		temp = store;
		t = first;
	}
	return first;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
