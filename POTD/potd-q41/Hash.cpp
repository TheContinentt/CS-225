#include <vector>
#include <string>
#include "Hash.h"
#include <iostream>

using namespace std;

int hashFunction(string s, int M) {
   // Your Code Here
   //hash function to sum up the ASCII characters of the letters of the string
	int sum = 0;
	for (char c : s)
	{
		sum += c;
	}
	sum = sum % M;
	return sum;
 }

int countCollisions (int M, vector<string> inputs) {
	int collisions = 0;
	// Your Code Here
	int size = inputs.size();
	int i = 0;
	int *store = new int[M];
	while (i < M)
	{
		store[i] = 0;
		i++;
	}
	i = 0;
	int retval;
	while (i < size)
	{
		retval = hashFunction(inputs[i], M);
		store[retval]++;
		i++;
	}
	i = 0;
	for (i = 0; i < M; i++)
	{
		if (store[i] > 1)
		{
			collisions += store[i] - 1;
		}
	}
	delete [] store;
	return collisions;
}
