#include "thing2.h"
#include "thing1.h"
#include <string>

std::string Thing2::foo()
{
	std::string s = "I will not eat them.";
	return s;
}
std::string Thing2::bar()
{
	std::string s = "And Ham";
	return s;
}
Thing2::~Thing2(){}
