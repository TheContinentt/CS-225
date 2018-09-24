#include "TreeNode.h"
#include <algorithm>

int getHeightBalance(TreeNode* root) {
  // your code here
	if (root == NULL)
		return 0;
	if (root->left_ == NULL && root->right_ == NULL)
		return 0;
	int left = getHeight(root->left_);
	if (root->left_ != NULL)
		left++;
	int right = getHeight(root->right_);
	if (root->right_ != NULL)
		right++;
	
  return (left - right);
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

