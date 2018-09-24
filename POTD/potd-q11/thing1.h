#ifndef THING1_H
#define THING1_H
#include <string>
//#include "thing2.h"
class Thing1{
public:
	std::string foo();
	virtual std::string bar();
	//std::string ~foo();
	//virtual ~bar();
	virtual ~Thing1();
};

#endif
