// Your code here!
#include "thing.h"
#include <string>

using namespace potd;
using namespace std;

Thing::Thing(int size)
{
	properties_ = new string[size];
	values_ = new string[size];
}
Thing::~Thing()
{
	delete [] properties_;
	delete [] values_;
}
Thing::Thing(const Thing &value)
{
	properties_ = new string[(&value)->props_ct_];
	values_ = new string[(&value)->props_ct_];
	for (int i = 0; i < (&value)->props_ct_; i++)
	{
		properties_[i] = (&value)->properties_[i];
		values_[i] = (&value)->values_[i];
	}
}
Thing & Thing::operator=(const Thing &value)
{
	delete [] this->properties_;
	delete [] this->values_;
	this->properties_ = new string[(&value)->props_ct_];
	this->values_ = new string[(&value)->props_ct_];
	for (int i = 0; i < (&value)->props_ct_; i++)
	{
		this->properties_[i] = (&value)->properties_[i];
		this->values_[i] = (&value)->values_[i];
	}
	return *this;
}	
int Thing::set_property(string name, string value)
{
	for (int i = 0; i < this->props_ct_; i++)
	{
		if (this->properties_[i] == name)
		{
			this->values_[i] = value;
			return i;
		}
		if (this->properties_[i] == string())
		{
			this->properties_[i] = name;
			this->values_[i] = value;
			return i;
		}
	}
	return -1;
}
string Thing::get_property(string name)
{
	for (int i = 0; i < this->props_ct_; i++)
	{
		if (this->properties_[i] == name)
		{
			return this->values_[i];
		}
	}
	return string();
}
