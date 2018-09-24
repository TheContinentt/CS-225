#include <vector>
#include <string>
#include <iostream>
#include "Hash.h"

unsigned long HashTable::bernstein(std::string str, int M)
{
    unsigned long b_hash = 5381;
    for (int i = 0; i < (int)str.length(); ++i)
    {
        b_hash = b_hash * 33 + str[i];
    }
    return b_hash % M;
};

HashTable::HashTable(int M)        // M is the size of the hash table
{
    table = new std::vector<std::string>(M);
    this->M = M;
	index_ = M - 1;
};

void HashTable::printKeys()        // Function to print all keys in the hash table
{
    for(int i = 0; i < M; ++i){
        for (auto it = table[i].begin() + 1; it!= table[i].end(); ++it)
	{
		index_++;
		if (index_ > M)
			break;
            std::cout<<*it<<std::endl;
	}
	break;
}
};

void HashTable::insert(std::string str)         //Inserts str into the hash table; must handle duplicates!
{
	if (index_ < 0)
		return;
	bool retval;
	retval = contains(str);
	if (retval == true)
		return;
	table[0].at(index_) = str;
	index_--;
	//std::cout << table[0] << "\n" << std::endl;
	return;
    // your code here
};

bool HashTable::contains(std::string str)       //Checks if the hash table contains str
{
    // your code here
	int index = M - 1;
	int retval = (int)bernstein(str, M);
	int flag = 0;
	int f = 0;
	while (index >= index_)
	{
		f = 1;
		std::string t = table[0].at(index);
		//std::cout << t << "\n" << std::endl;
		int temp = (int)bernstein(t, M);
		if (temp == retval)
		{
			flag = 1;
			break;
		}
		index--;
	}
	if (flag == 1 && f == 1)
		return true;
	return false;
};

