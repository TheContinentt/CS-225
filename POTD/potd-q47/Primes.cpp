#include <vector>
#include "Primes.h"

std::vector<int> *genPrimes(int M) {
    std::vector<int> *v = new std::vector<int>();
    // your code here
	v->push_back(2);
	for (int  i =  3;  i < M;  ++i)
        {
            bool  isPrime  =  true ;
            for (int  j =  2;  j < i;  ++j)
            {
                if (i  % j ==  0)
                {
                    isPrime  =  false ;
                    break ;
                }
            }
            if (isPrime)
            {
                v->push_back(i);
            }
        }
    return v;
}

int numSequences(std::vector<int> *primes, int num) {

    // your code here

	int temp = 0;
	while ((*primes)[temp] <= num)
		temp++;
	int freq = 0;
	int sum;
	for (int i = 0; i <= temp; i++)
	{
		sum = 0;
		for (int k = i; k <= temp; k++)
		{
			sum += (*primes)[k];
			if (sum == num)
				freq++;
			if (sum > num)
				break;
		}
	}
	return freq;
    // code to quell compiler complaints.  Delete it.
   // return num + (*primes)[1];
}
