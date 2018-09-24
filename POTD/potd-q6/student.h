// Your code here! :)
#ifndef student_H
#define student_H
#include <string>

using namespace std;

namespace potd{
class student
{
private:
	string name_;
	int grade_;
public:
	student();
	void set_name(string Newname);
	string get_name();
	void set_grade(int NewGrade);
	int get_grade();
};
}

#endif
