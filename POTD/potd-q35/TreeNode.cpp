#include "TreeNode.h"
#include <algorithm>

bool isHeightBalanced(TreeNode* root) {
  // your code here
	bool retval;
	int difference, left, right;
	left = getHeight(root->left_);
	right = getHeight(root->right_);
	retval = (right == left);
  return retval;
}


int getHeight(TreeNode* root)
{
	int retval;
	if (root == NULL)
		return 0;
	if (root->left_ == NULL && root->right_ == NULL)
		return 0;
	if (root->left_ == NULL)
		return 1 + getHeight(root->right_);
	if (root->right_ == NULL)
		return 1 + getHeight(root->left_);
	retval = 1 + fmax(getHeight(root->left_), getHeight(root->right_));
	return retval;
}


void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

