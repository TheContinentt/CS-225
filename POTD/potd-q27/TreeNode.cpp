#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int TreeNode::getHeight() {
	int retval;
	if (this->left_ == NULL && this->right_ == NULL)
		return 0;
	if (this->left_ == NULL)
		return 1 + (this->right_)->getHeight();
	if (this->right_ == NULL)
		return 1 + (this->left_)->getHeight();
	retval = 1 + max((this->left_)->getHeight(), (this->right_)->getHeight());
	return retval;
}
