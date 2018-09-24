#include "TreeNode.h"
#include <algorithm>

TreeNode* findLastUnbalanced(TreeNode* root) {
  // your code here
	int left;
	int right;
	if (root == NULL)
		return NULL;
	left = getHeight(root->left_);
	right = getHeight(root->right_);
	if (left == right || left == right + 1 || left == right - 1)
	{
		TreeNode* A = findLastUnbalanced(root->left_);
		TreeNode* B = findLastUnbalanced(root->right_);
		if (getHeight(A) > getHeight(B))
			return A;
		else
			return B;
	}
	return root;
//  return NULL;
}

int getHeight(TreeNode* root)
{
	int retval;
	if (root == NULL)
		return 0;
	if (root->left_ == NULL && root->right_ == NULL)
		return 1;
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

