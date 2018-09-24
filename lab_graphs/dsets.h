/* Your code here! */
#ifndef _DSETS_H_
#define _DSETS_H_
#include <vector>
using std::vector;

class DisjointSets
{
	public:
		DisjointSets();
		int find(int elem);
		void addelements(int num);
		void setunion(int a, int b);
	private:
		vector<int> store;
};

#endif
