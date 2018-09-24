#ifndef THING2_H
#define THING2_H
#include <string>
#include "thing1.h"
//#include "thing1.cpp"
class Thing2 : public Thing1{
public:
	std::string foo();
	std::string bar();
	virtual ~Thing2();
};
#endif
