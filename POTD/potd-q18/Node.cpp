#include "Node.h"

using namespace std;

void sortList(Node **head) {
  // your code here!
	if (*head == NULL)
	{
		return;
	}
	if ((*head)->next_ == NULL)
	{
		return;
	}
	Node *temp = *head;
	*head = (*head)->next_;
	sortList(head);
	Node *t = *head;
	Node *pv = NULL;
	Node *next = (*head)->next_;
	while (t != NULL)
	{
		if ((*head)->next_ == NULL && pv == NULL)
		{
			if (temp->data_ > (*head)->data_)
			{
				(*head)->next_ = temp;
				temp->next_ = NULL;
				break;
			}
			else
			{
				temp->next_ = *head;
				*head = temp;
				break;
			}
		}
		else if (next == NULL)
		{
			t->next_ = temp;
			temp->next_ = NULL;
			break;
		}
		else
		{
			if (t->data_ > temp->data_)
			{
				temp->next_ = t;
				*head = temp;
				break;
			}
			else if (next->data_ > temp->data_)
			{
				t->next_ = temp;
				temp->next_ = next;
				break;
			}
			else
			{
				pv = t;
				t = t->next_;
				next = next->next_;
			}
		}
	}
	return;
	
	
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

