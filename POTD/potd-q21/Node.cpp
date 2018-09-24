#include "Node.h"

using namespace std;

Node *listIntersection(Node *first, Node *second) {
  // your code here
	int flag = 0;
	if (first == NULL && second == NULL)
		return second;
	else if (first == NULL && second != NULL)
		return first;
	else if (first != NULL && second == NULL)
		return second;
	else
	{
		Node *st = second;
		Node *ft = first;
		Node *head = st;
		Node *start = new Node();
		while (st != NULL)
		{
			while (ft != NULL)
			{
				if (st->data_ == ft->data_ && flag == 0)
				{
					start->data_ = st->data_;
					start->next_ = NULL;
					head = start;
					flag = 1;
					break;
				}
				else if (st->data_ == ft->data_ && flag == 1)
				{
					Node *s = new Node();
					s->data_ = st->data_;
					head->next_ = s;
					s->next_ = NULL;
					head = head->next_;
					break;
				}
				ft = ft->next_;
			}
			if (st->next_ == NULL)
				break;
			else if (st->data_ == st->next_->data_)
			{
				while (st->data_ == st->next_->data_)
				{
					st = st->next_;
					if (st->next_ == NULL)
						break;
				}
				st = st->next_;
			}
			else
			{
				st = st->next_;
			}
		}
		if (flag == 0)
		{
			delete start;
			return NULL;
		}
		return start;
	}
			
//  return NULL;
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
