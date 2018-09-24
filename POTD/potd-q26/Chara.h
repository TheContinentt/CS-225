#ifndef _CHARA_H
#define _CHARA_H

#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Node
{
	Node *next;
	string name_;
};

class Chara {
    public:
	Chara();
        string getStatus() const;
        int size() const;
        void addToQueue(string name);
        string popFromQueue();
    private:
	int size_;
	Node *head_;
	Node *tail_;
};

#endif
