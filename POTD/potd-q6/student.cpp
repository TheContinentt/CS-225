// Your code here! :)
#include <string>
#include "student.h"
#include <iostream>

using namespace std;
namespace potd{
student::student()
{
	name_ = "Sally";
	grade_ = 5;
}
void student::set_name(string NewName)
{
	name_ = NewName;
}
string student::get_name()
{
	return name_;
}
void student::set_grade(int grade)
{
	grade_ = grade;
}
int student::get_grade()
{
	return grade_;
}
}
