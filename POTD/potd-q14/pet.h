// pet.h
#ifndef _PET_H
#define _PET_H
#include "animal.h"
#include <string>
#include <iostream>

using namespace std;

class Pet : public Animal
{
	private:
		string name_;
		string owner_name_;
		string type_;
		string food_;
	public:
		Pet();
		Pet(string type, string food, string name, string ownername);
		void setFood(string nu_food);
        	string getFood();
        	void setName(string nu_type);
        	string getName();
        	string print();
		void setOwnerName(string nu_ownername);
        	string getOwnerName();
		void setType(string nu_type);
	        string getType();
};
#endif
