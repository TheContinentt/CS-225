// pet.cpp
#include "pet.h"
#include <string>
#include "animal.h"
#include <iostream>

using namespace std;

Pet::Pet()
{
	type_ = "cat";
	name_ = "Fluffy";
	food_ = "fish";
	owner_name_ = "Cinda";
}

Pet::Pet(string type, string food, string name, string ownername)
{
	type_ = type;
	name_ = name;
	food_ = food;
	owner_name_ = ownername;
}


void Pet::setType(string nu_type) {
    type_ = nu_type;
}

string Pet::getType() {
    return type_;
}

void Pet::setFood(string nu_food) {
    food_ = nu_food;
}

string Pet::getFood() {
    return food_;
}

void Pet::setName(string nu_type) {
    name_ = nu_type;
}

string Pet::getName() {
    return name_;
}

void Pet::setOwnerName(string nu_ownername) {
    owner_name_ = nu_ownername;
}

string Pet::getOwnerName() {
    return owner_name_;
}

string Pet::print() {
    return "My name is " + name_;
}
