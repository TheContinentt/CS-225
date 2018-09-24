// Your code here! :)
#include <iostream>
#include "student.h"
#include "q6.h"
#include <string>

using namespace std;
using namespace potd;

int main()
{
	student ss;
	student &s = ss;// = new student();
	//(&s)->student();
	int g = (&s)->get_grade();
	cout << g << endl;
	graduate(s);
	g = (&s)->get_grade();
	cout << g << endl;
	//delete s;
	return 0;
}
