#include "list.h"
#include <iostream>
//#include "list-inl.h"
//#include "list-given-inl.h"

using namespace std;
int main() {
	List<int> list;
	List<int> listt;	
  /*for (unsigned i = 300; i > 250; i--) 
{
	//unsigned n = 2 
	 list.insertFront(i); }
for (unsigned i = 100; i > 50; i--) 
{
	list.insertFront(i);
}
	for (unsigned i = 200; i > 150; i--) { listt.insertFront(i); }*/
	/*for (unsigned i = 50; i > 0; i--) { listt.insertFront(i); }
	listt.mergeWith(list);*/
	listt.insertBack(6);
	listt.insertBack(1);
	listt.insertBack(5);
	listt.insertBack(8);
	listt.insertBack(4);
	listt.insertBack(3);
	listt.insertBack(7);
	listt.insertBack(2);
	listt.insertBack(9);
	listt.sort();
	//List<int> listtt = <1,2,3>;
	//list = list.split(2);
	/*ListNode *temp = list.head_;
	while (temp != NULL)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}*/
	//cout << list.head_ << endl;
	//cout << list.tail_ << endl;
  return 0;
}
