/* Your code here! */
#include "dsets.h"
#include <vector>

DisjointSets::DisjointSets()
{
	std::vector<int> temp;
	store = temp;
}

void DisjointSets::addelements(int num)
{
	while (num > 0)
	{
		store.push_back(-1);
		num--;
	}
}

int DisjointSets::find(int elem)
{
	if (store[elem] < 0)
		return elem;
	int temp = find(store[elem]);
	store[elem] = temp;
	return temp;
}

void DisjointSets::setunion(int a, int b)
{
	int ret = a;
	int retval = b;
	if (store[a] >= 0)
		ret = find(a);
	if (store[b] >= 0)
		retval = find(b);
	int sum = store[ret] + store[retval];
	if (store[ret] < store[retval])
	{
		store[retval] = ret;
		store[ret] = sum;
	}
	else
	{
		store[ret] = retval;
		store[retval] = sum;
	}
}


