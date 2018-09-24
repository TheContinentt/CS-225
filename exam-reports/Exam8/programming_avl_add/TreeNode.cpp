#include "TreeNode.h"
#include <iostream>
#include <cmath>

// Part 1 code

void rotateRight(TreeNode *& root) {

    TreeNode *nuRoot = root->left_;
    root->left_ = nuRoot->right_;
    nuRoot->right_ = root;

    root = nuRoot;

    updateHeight(root);
    updateHeight(root->right_);
    return;
}


void rotateLeft(TreeNode *& root) {

    TreeNode *nuRoot = root->right_;
    root->right_ = nuRoot->left_;
    nuRoot->left_ = root;

    root = nuRoot;

    updateHeight(root);
    updateHeight(root->left_);
    return;
}

void rotateLeftRight(TreeNode* &root) {
    rotateLeft(root->left_);
    rotateRight(root);
}


void rotateRightLeft(TreeNode* &root) {
    rotateRight(root->right_);
    rotateLeft(root);
}

// Your Code

void insert(TreeNode* &root, int val) {
    // Your code here
	if (root == NULL)
	{
		TreeNode* create = new TreeNode(val);
		root = create;
		return;
	}
	if (root->val_ < val)
	{
		insert(root->right_, val);
	}
	else if (root->val_ > val)
	{
		insert(root->left_, val);
	}
	rebalance(root);
	updateHeight(root);
	return;
    // The following lines are to silence compiler warnings.  Delete it.
    //val = 0;
    //root = NULL;
}

void rebalance(TreeNode* &root) {
    // The following line is to silence compiler warnings.  Delete it.
	int lh;
	int rh;
	int cl;
	int cr;
	lh = heightOrNeg1(root->left_);
	rh = heightOrNeg1(root->right_);
	if (lh - rh > 1)
	{
		cl = heightOrNeg1(root->left_->left_);
		cr = heightOrNeg1(root->left_->right_);
		if (cl > cr)
		{
			rotateRight(root);
		}
		else
		{
			rotateLeftRight(root);
		}
	}
	else if (rh - lh > 1)
	{
		cl = heightOrNeg1(root->right_->left_);
		cr = heightOrNeg1(root->right_->right_);
		if (cl > cr)
		{
			rotateRightLeft(root);
		}
		else
		{
			rotateLeft(root);
		}
	}
	
    //root = NULL;
    return;
}

// Helper functions

int heightOrNeg1(TreeNode *root) {
    if (root==NULL)
        return -1;
    else
        return root->height_;
}

void updateHeight(TreeNode * node) {
    node->height_ = 1 + std::max(heightOrNeg1(node->right_), heightOrNeg1(node->left_));
}

using namespace std;

void show(TreeNode *t1) {
    if (t1==NULL) {
        cout << "x";
        return;
    }

    if (t1->left_ == NULL && t1->right_==NULL) {
        cout << t1->val_;
        return;
    }

    cout << "(" << t1-> val_ << " ";
    show(t1->left_);
    cout << " ";
    show(t1->right_);
    cout << ")";
}

void deleteTree(TreeNode* root)
{
    if (root == NULL) return;
    deleteTree(root->left_);
    deleteTree(root->right_);
    delete root;
    root = NULL;
}

