#include "Node.h"

using namespace std;

void mergeList(Node *first, Node *second) {
  // your code here!
	//int firstnumber = first->getNumNodes();
	//int secondnumber = second->getNumNodes();
	if (first == NULL)
	{
		first = second;
		return;
	}
	else if (second == NULL)
	{
		return;
	}
	Node *temp = first;
	Node *t = second;
	Node *sf;
	Node *ss;
	Node *pf;
	Node *ps;
	while (temp != NULL && t != NULL)
	{
		pf = temp;
		ps = t;
		sf = temp->next_;
		ss = t->next_;
		temp->next_ = t;
		t->next_ = sf;
		temp = sf;
		t = ss;
	}
	if (temp == NULL && t == NULL)
	{
		return;
	}
	else if (temp == NULL)
	{
		ps->next_ = t;
		return;
	}
	else if (t == NULL)
	{
		//temp->next_ = temp;
		return;
	}
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

