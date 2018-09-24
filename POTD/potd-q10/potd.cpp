// your code here!
#include "potd.h"
#include <iostream>
      /* pow */
//using namespace potd;
using namespace std;

int *potd::raise(int *arr)
{
	int i = 0;
	while (arr[i] >= 0 )
	{
		i++;
	}
	i++;
	int *newarray = new int[i];
	for (int n = 0; n <= i - 3; n++)
	{
		newarray[n] = pow(arr[n], arr[n+1]);
	}
	newarray[i-2] = arr[i - 2];
	newarray[i-1] = -1;
	return newarray;
}
