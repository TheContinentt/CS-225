#include <vector>
#include "BTreeNode.h"


std::vector<int> traverse(BTreeNode* root) {
    // your code here
    std::vector<int> v;
	/*int i;
	int j;
	int counter = 0;
	if (root->is_leaf_ == true)
	{
		i = root->elements_.size();
		while (counter < i)
		{
			v.push_back(root->elements_[counter]);
			counter++;
		}
		return v;
	}
	i = root->children_.size();
	j = root->elements_.size();
	while (counter < i)
	{
		v = traverse(root->children_[counter]);
		if (counter < j)
		{
			v.push_back(root->elements_[counter]);
		}
		counter++;
	}*/
	v = traversehelper(root, v);
    return v;
}

std::vector<int> traversehelper(BTreeNode* root, std::vector<int> v) {
    // your code here
    //std::vector<int> v;
	int i;
	int j;
	int counter = 0;
	if (root->is_leaf_ == true)
	{
		i = root->elements_.size();
		while (counter < i)
		{
			v.push_back(root->elements_[counter]);
			counter++;
		}
		return v;
	}
	i = root->children_.size();
	j = root->elements_.size();
	while (counter < i)
	{
		v = traversehelper(root->children_[counter], v);
		if (counter < j)
		{
			v.push_back(root->elements_[counter]);
		}
		counter++;
	}
    return v;
}
