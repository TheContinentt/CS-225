// Your code here! :)
#include "student.h"

using namespace std;

namespace potd{
void graduate(student &s)
{
	int grade = (&s)->get_grade();
	grade = grade + 1;
	(&s)->set_grade(grade);
}
}
