#include "potd.h"
#include <iostream>

using namespace std;

void insertSorted(Node **head, Node *insert) {
  // your code here!
	//Node *read = *head;
	int f = 0;
	if (*head == NULL)
	{
		//(**head).next_ = insert->next_;
		//(**head).data_ = insert->data_;
		*head = insert;
		f = 1;
	}
	Node *prev = NULL;
	Node *next = (*head)->next_;
	Node *read = *head;
	Node *temp;
	while (read != NULL && f == 0)
	{
		if (next == NULL)
		{
			if (read->data_ < insert->data_)
			{
				read->next_ = insert;
				f = 1;
				break;
			}
			else if (read->data_ >= insert->data_)
			{
				temp = *head;
				*head = insert;
				(*head)->next_ = temp;
				f = 1;
				break;
			}
		}	
		else
		{
			if (prev == NULL && read->data_ >= insert->data_)
			{
				temp = *head;
				*head = insert;
				(*head)->next_ = temp;
				break;
			}
			else if ((read->data_ < insert->data_) && (insert->data_ <= next->data_))
			{
				read->next_ = insert;
				insert->next_ = next;
				f = 1;
				break;
			}
			else
			{
				prev = read;
				read = read->next_;
				next = next->next_;
				continue;
			}
		}
	}
}
