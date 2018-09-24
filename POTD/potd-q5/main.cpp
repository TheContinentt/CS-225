// your code here
#include <iostream>
#include "food.h"
#include "q5.h"
#include <string>

using namespace std;

int main()
{
	food *f = new food();
	int q = f->get_quantity();
	string s = f->get_name();
	cout<< "You have " << q << " " << s << "s." <<endl;
	increase_quantity(f);
	q = f->get_quantity();
	cout<< "You have " << q << " " << s << "s." <<endl;
	delete f;
	return 0;
}
