#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Hash.h"

unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	for (int i = 0; i < (int) str.length(); ++i)
	{
		b_hash = b_hash * 33 + str[i];
	}
	return b_hash % M;
}

float hash_goodness(std::string str, int M)
{
    std::vector<int>* array = new std::vector<int>(M);	// Hint: This comes in handy
	int permutation_count = 0;	
	float goodness = 0;
	int retval;
	int index = 0;
	do {
		if (permutation_count == M){
			break;
		}
		// Code for computing the hash and updating the array
		retval = bernstein(str, M);
		//std::cout << str << "\n" << std::endl;
		//array[index] = (int)retval;
		//array->push_back((int)retval);
		array->at(index) = retval;
		index++;
		permutation_count++;

	} while(std::next_permutation(str.begin(), str.end()));
	
	//Code for determining goodness
	retval = countCollisions(M, *array);
	goodness = float(retval) / index;
	//goodness = retval / M;
	return goodness;
}

int countCollisions(int M, std::vector<int> inputs) {
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
		retval = inputs[i];
		store[retval]++;
		i++;
	}
	i = 0;
	for (i = 0; i < M; i++)
	{
		if (store[i] > 1)
		{
			collisions += (store[i] - 1);
		}
	}
	delete [] store;
	return collisions;
}
