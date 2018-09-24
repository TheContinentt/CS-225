#include <vector>
#include <bits/stdc++.h>
#include "Primes.h"

std::vector<int> *genPrimes(int M) {
    std::vector<int> *v = new std::vector<int>();
    // your code here
	int check[M + 1];
	std::memset(check, 0, sizeof(check));
	for (int p=2; p*p<=M; p++)
    	{
		if (check[p] == 0)
        	{
			for (int i=p*2; i<=M; i += p)
                	check[i] = 1;
        	}
	}
	for (int p=2; p<=M; p++)
	{
		if (check[p] == 0)
			v->push_back(p);
	}
    return v;
}
