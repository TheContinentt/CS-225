#include "potd.h"
#include <iostream>
#include <string>

using namespace std;

string stringList(Node *head) {
    // your code here!
	Node *temp = head;
	if (head == NULL)
	{
		return "Empty list";
	}
	string s;
	int counter = 0;
	while (temp != NULL)
	{
		std::string s1 = std::to_string(counter);
		std::string s2 = std::to_string(temp->data_);
		if (temp == head)
		{
			s = "Node " + s1 + ": " + s2;
		}
		else
		{
			s = s + " -> Node " + s1 + ": " + s2;
		}
		temp = temp->next_;
		counter++;
	}
	return s;
}

