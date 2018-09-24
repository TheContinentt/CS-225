// your code here
#include "Chara.h"
#include <string>
#include <queue>

Chara::Chara()
{
	size_ = 0;
	head_ = NULL;
	tail_ = NULL;
}

int Chara::size() const {
	return size_;
//  return 0;
}

string Chara::getStatus() const
{
	if (size_ == 0)
		return "Empty";
	else if (size_ <= 3)
		return "Light";
	else if (size_ <= 6 && size_ >= 4)
		return "Moderate";
	else
		return "Heavy";
}

void Chara::addToQueue(string name)
{
	if (size_ == 0)
	{
		head_ = new Node();
		head_->next = NULL;
		head_->name_ = name;
		tail_ = head_;
		size_++;
	}
	else
	{
		Node *temp = new Node();
		temp->name_ = name;
		temp->next = NULL;
		tail_->next = temp;
		//curr = tail;
		tail_ = temp;
		size_++;
	}
}

string Chara::popFromQueue()
{
	if (size_ == 0)
		return "Can not pop from the queue.";
	else if (size_ == 1)
	{
		string v = head_->name_;
		delete head_;
		head_ = NULL;
		size_--;
		return v;
	}
	else
	{
		string v = head_->name_;
		Node *temp = head_->next;
		delete head_;
		head_ = NULL;
		head_ = temp;
		size_--;
		return v;
	}
}




