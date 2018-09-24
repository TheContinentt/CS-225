#include "Node.h"

using namespace std;

Node *listSymmetricDifference(Node *first, Node *second) {
  // your code here
		/*Node *start = new Node();
		return first;*/
	if (first == NULL && second == NULL)
		return NULL;
	else if (first == NULL && second != NULL)
		return second;
	else if (first != NULL && second == NULL)	
		return first;
	else
	{
		Node *ft = first;
		Node *st = second;
		int flag = 0;
		int f = 0;
		Node *start = new Node();
		Node *pv = start;
		while (ft != NULL)
		{
			while (st != NULL)
			{
				if (ft->data_ == st->data_)
				{
					flag = 1;
					break;
				}
				st = st->next_;
			}
			if (flag == 0 && f == 0)
			{
				//Node *temp = new Node();
				start->data_ = ft->data_;
				start->next_ = NULL;
				pv = start;
				f = 1;
			}
			else if (flag == 0 && f == 1 && pv->data_ != ft->data_)
			{
				Node *temp = new Node();
				temp->next_ = NULL;
				temp->data_ = ft->data_;
				pv->next_ = temp;
				pv = temp;
			}
			ft = ft->next_;
			st = second;
			flag = 0;
		}
		ft = first;
		st = second;
		while (st != NULL)
		{
			while (ft != NULL)
			{
				if (ft->data_ == st->data_)
				{
					flag = 1;
					break;
				}
				ft = ft->next_;
			}
			if (flag == 0 && f == 0)
			{
				//Node *temp = new Node();
				start->data_ = st->data_;
				start->next_ = NULL;
				pv = start;
				f = 1;
			}
			else if (flag == 0 && f == 1 && pv->data_ != st->data_)
			{
				Node *temp = new Node();
				temp->next_ = NULL;
				temp->data_ = st->data_;
				pv->next_ = temp;
				pv = temp;
			}
			st = st->next_;
			ft = first;
			flag = 0;
		}
		if (f == 0)
		{
			delete start;
			return NULL;
		}
		/*pv = start;
		Node *t = start;
		Node *s;
		Node *c;
		while (t != NULL)
		{
			c = t->next_;
			while (c != NULL)
			{
				if (c->data_ == t->data_)
				{
					s = c->next_;
					pv->next_ = c->next_;
					delete c;
					c = s;
				}
				else
					c = c->next_;
			}
			c = t->next_;
			t = t->next_;
		}*/
		Node *ptr1;
		Node *ptr2;
		Node *dup;
    		ptr1 = start;
 
    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->next_ != NULL)
    {
        ptr2 = ptr1;
 
        /* Compare the picked element with rest
           of the elements */
        while (ptr2->next_ != NULL)
        {
            /* If duplicate then delete it */
            if (ptr1->data_ == ptr2->next_->data_)
            {
                /* sequence of steps is important here */
                dup = ptr2->next_;
                ptr2->next_ = ptr2->next_->next_;
                delete(dup);
            }
            else /* This is tricky */
                ptr2 = ptr2->next_;
        }
        ptr1 = ptr1->next_;
    }
		return start;
	}
  //return NULL;
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
