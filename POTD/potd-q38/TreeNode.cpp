#include "TreeNode.h"
#include <algorithm>


void rightRotate(TreeNode* root) {

    // Your code here
	TreeNode* temp = root->left_;
	TreeNode* t = temp->right_;
	root->left_ = t;
	t->parent_ = root;
	temp->right_ = root;
	root = temp;
	root->parent_ = NULL;
	root->right_->parent_ = root;

}


void leftRotate(TreeNode* root) {

    // your code here
	TreeNode* temp = root->right_;
	TreeNode* t = temp->left_;
	root->right_ = t;
	t->parent_ = root;
	temp->left_ = root;
	root = temp;
	root->parent_ = NULL;
	root->left_->parent_ = root;


}



void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

