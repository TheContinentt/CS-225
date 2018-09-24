// Your code here
#include <string>
#include "food.h"
#include <iostream>

using namespace std;
food::food()
{
	name_ = "apple";
	quantity_ = 5;
}

void food::set_name(string newName)
{
	name_ = newName;
}

void food::set_quantity(int newQuantity)
{
	quantity_ = newQuantity;
}

string food::get_name()
{
	return name_;
}

int food::get_quantity()
{
	return quantity_;
}

