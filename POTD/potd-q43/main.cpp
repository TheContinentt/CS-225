#include <string>
#include <iostream>
#include "Hash.h"

int main()
{
    std::string s = "arbitrary";
    std::string ss = "ary";
	for (int i = 51; i <= 100; ++i)//51, 100
	{	
        std::cout<<"Goodness of hash Bernstein hash function for \""<<s<<"\" with range="<<i<<" is: "<<hash_goodness(s,i)<< std::endl;	
	}	

}
