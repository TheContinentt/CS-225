#include "thing1.h"
//#include "thing2.h"
#include <string>

std::string Thing1::foo()
{
	std::string s = "Sam I Am";
	return s;
}
std::string Thing1::bar()
{
	std::string s = "Green Eggs";
	return s;
}
Thing1::~Thing1(){}
