#include "Exam.h"
#include "LNode.h"
#include <iostream>
#include "Node.h"
using namespace std;

void populate(Node **arr, int n) {
    // your code here
	LNode *na = new LNode[n];
	/*for (int i = 0; i < n; i++)
	{
		na[i]->setLookingAt(NULL);
	}*/
	for (int i = 0; i < n; i++)
	{
		Node *temp;
		temp = &na[i];
		arr[i]->setLookingAt(temp);
	}
}

void lookPrev(Node **arr, int n) {
    // your code here
	for (int i = 1; i < n; i++)
	{
		Node *temp;
		temp = arr[i-1]->getLookingAt();
		arr[i]->setLookingAt(temp);
	}
	arr[0]->setLookingAt(NULL);
}

void display(Node **arr, int n) {
    Node *x;
    for(int i=0; i<n; i++) {
        x = arr[i]->getLookingAt();
        if (x)
            cout << "Node " << arr[i] << " is looking at " << x << "." << endl;
        else
            cout << "Node " << arr[i] << " is looking at NULL." << endl;
    }
}
