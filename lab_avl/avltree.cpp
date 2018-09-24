/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <cmath>
#include <algorithm>

/*template <class K, class V>
int AVLTree<K, V>::getHeight(Node*& root)
{
	int retval;
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 0;
	if (root->left == NULL)
		return 1 + getHeight(root->right);
	if (root->right == NULL)
		return 1 + getHeight(root->left);
	retval = 1 + fmax(getHeight(root->left), getHeight(root->right));
	return retval;
}*/

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
	//Node* temp = t->right;
	//temp = t->right;
	/*Node* templeft = t->right;
	while (templeft->left != NULL)
	{
		templeft = templeft->left;
	}
	templeft->left = t;
	templeft->left->right = NULL;
	//temp->left->left = NULL;
	//temp->right = t->right->right;
	t = temp;*/
	Node* old = t;
    	Node* temp = t->right->left;
  	t = t->right;
   	t->left = old;
    	old->right = temp;
    	old->height = fmax(heightOrNeg1(old->left), heightOrNeg1(old->right)) + 1;
	t->height = fmax(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
	//Node* temp = t->left;
	//temp = t->left;
	/*Node* tempright = t->left;
	while (tempright->right != NULL)
	{
		tempright = tempright->right;
	}
	tempright->right = t;
	tempright->right->left = NULL;
	//temp->right->right = NULL;
	//temp->left = t->left->left;
	t = temp;*/
	Node* old = t;
   	Node* temp = t->left->right;
    	t = t->left;
   	t->right = old;
   	old->left = temp;
	old->height = fmax(heightOrNeg1(old->left), heightOrNeg1(old->right)) + 1;
	t->height = fmax(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	//Node* temp = subtree;
	int newleftheight;
	int newrightheight;
	if (subtree == NULL)
		return;
	newleftheight = heightOrNeg1(subtree->left);
	newrightheight = heightOrNeg1(subtree->right);
	if (newleftheight - newrightheight > 1)
	{
		if (heightOrNeg1(subtree->left->left) > heightOrNeg1(subtree->left->right))
		{
			rotateRight(subtree);
		}
		else
		{
			rotateLeftRight(subtree);
		}
	}
	else if (newleftheight - newrightheight < -1)
	{
		if (heightOrNeg1(subtree->right->right) > heightOrNeg1(subtree->right->left))
		{
			rotateLeft(subtree);
		}
		else
		{
			rotateRightLeft(subtree);
		}
	}
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
	if (subtree == NULL)
	{
		subtree = new Node(key, value);
		return;
	}
	else if (subtree->key >= key)
	{
		insert(subtree->left, key, value);
	}
	else
	{
		insert(subtree->right, key, value);
	}
	subtree->height = fmax(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
	rebalance(subtree);
	return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
	remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
	remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
		delete subtree;
		subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
		/*Node* temp = subtree->right;
		Node* templeft = subtree->left;
		delete subtree;
		subtree = templeft;*/
		Node* temp = subtree->left;
		while (temp->right != NULL)
		{
			temp = temp->right;
		}
		swap(subtree, temp);
		remove(subtree->left, key);
		
		
        } else {
            /* one-child remove */
            // your code here
		if (subtree->left == NULL)
		{
			Node* temp = subtree->right;
			delete subtree;
			subtree = temp;
		}
		else
		{
			Node* temp = subtree->left;
			delete subtree;
			subtree = temp;
		}
        }
        // your code here
	//rebalance(subtree);
    }
	rebalance(subtree);
}
