#include <vector>
#include <string>

vector<string> NoProblem(int start, vector<int> created, vector<int> needed) {

    // your code here
	int size_ = created.size();
	int i = 0;
	std::vector<string> store(size_);
	while (i < size_)
	{
		if (start >= needed[i])
		{
			store[i] = "No problem! :D";
			start = start + created[i] - needed[i];
			i++;
		}
		else
		{
			store[i] = "No problem. :(";
			start = start + created[i];
			i++;
		}
	}
	return store;
}
