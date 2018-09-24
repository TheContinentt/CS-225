// Your code here
#include "potd.h"
#include <string>
#include <iostream>

using namespace std;

string getFortune(const string &s)
{
	int i = s.length() % 7;
	cout << i << endl;
	if (i == 1)
	{
		return "As you wish";
	}
	else if (i == 2)
		return "Nec spe nec metu!";
	else if (i == 3)
		return "Do, or do not. There is no try.";
	else if (i == 4)
		return "This fortune intentionally left blank.";
	else if (i == 5)
		return "Amor Fati!";
	else if (i == 6)
		return "Amor Fati!!!";
	else if (i == 0)
		return "What are you babbling about?!";
}
