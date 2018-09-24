// your code here
#include "food.h"

using namespace std;

void increase_quantity(food *f)
{
	int m = f->get_quantity();
	m = m + 1;
	f->set_quantity(m);
}

