#include "potd.h"
#include <iostream>
using namespace std;

int main() {
  // Test 1: An empty list
  Node * head = NULL;
  cout << stringList(head) << endl;

  // Test 2: A list with exactly one node
	Node *headd = new Node;
	headd->data_ = 100;
	headd->next_ = NULL;
	cout << stringList(headd) << endl;
	delete headd;
  // Test 3: A list with more than one node
	Node *headdd = new Node;
	Node *nextt = new Node;
	Node *third = new Node;
	headdd->data_ = 100;
	headdd->next_ = nextt;
	nextt->data_ = 200;
	nextt->next_ = third;
	third->data_ = 300;
	third->next_ = NULL;
	cout << stringList(headdd) << endl;
	delete headd;
	delete nextt;
	delete third;
  return 0;
}
