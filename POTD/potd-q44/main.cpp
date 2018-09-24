#include <string>
#include <iostream>
#include<algorithm>
#include <vector>
#include "Hash.h"

int main()
{
	HashTable h(10);
	//h.insert("aaa");
	h.insert("aaa");
	h.insert("ccc");
	h.insert("ddd");
	//std::cout << h.table[0] << "\n" << std::endl;
	h.insert("eee");
	h.insert("fff");
	h.insert("ggg");
	h.insert("hhh");
	h.insert("jjj");
	h.insert("asbjfadss");
	h.insert("asbjfahjghjss");
	h.insert("asbjfadassss");
	h.insert("asbjfadfdgfdgs");
	h.insert("asbjfadsadsa");
    std::cout<<"Does the hash table contain bbb? "<<h.contains("bbb")<<"\n";
	std::cout<<"Does the hash table contain aaa? "<<h.contains("aaa")<<"\n";
	std::cout<<"Contents of the hash table:\n";	
	h.printKeys();
}
