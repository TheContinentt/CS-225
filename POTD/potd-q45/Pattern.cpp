#include "Pattern.h"
#include <string>
#include <iostream>
#include <map>

bool wordPattern(std::string pattern, std::string str) {
	std::map<char, string> mymap;
	std::string temp;
	int index = 0;
	for (char d: pattern)
	{
		index++;
	}
	std::string *store = new std::string[index];
	index = 0;
	int flag = 0;
	for (char c: str)
	{
		if (c == ' ')
		{
			flag = 1;
		}
		if (flag == 0)
		{
			temp += c;
		}
		if (flag == 1)
		{
			store[index] = temp;
			temp.clear();
			flag = 0;
			std::cout << store[index] << "" << std::endl;
			index++;
		}
	}
	store[index] = temp;
	std::cout << store[index] << "" << std::endl;
	index = 0;
	for (char e: pattern)
	{
		mymap.insert(pair<char, string>(e, store[index]));// = store[index];
		index++;
	}
	index = 0;
	for (char e: pattern)
	{
		std::cout << mymap.find(e)->second << " " << mymap.find(e)->first << std::endl;
		index++;
	}
	bool test = true;
	index = 0;
	for (char g: pattern)
	{
		if (mymap.find(g)->second != store[index])
		{
			test = false;
			break;
		}
		index++;
	}
	bool reversetest = true;
	index = 0;
	std::string ttt = store[0];
	char z;
	for (char g: pattern)
	{
		if (index == 0)
		{
			z = g;
			index++;
			continue;
		}
		if (mymap.find(g)->first == z)
			continue;
		if (mymap.find(g)->second == ttt)
		{
			reversetest = false;
			break;
		}
		index++;
	}
	return (test && reversetest);
	//return test;
    //write your code here
}

