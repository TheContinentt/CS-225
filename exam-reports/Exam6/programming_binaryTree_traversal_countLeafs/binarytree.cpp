#define _BINARYTREE_CPP
#include "binarytree.h"
#include <iostream>
#include <cstdlib>

using namespace std;


template <typename T>
int BinaryTree<T>::countLeafNodes() {
	int retval;
	retval = count(root);
  return retval;
}

template <typename T>
int BinaryTree<T>::count(Node *subroot)
{
	int retval = 0;
	if (subroot == NULL)
		return 0;
	if (subroot->left == NULL && subroot->right == NULL)
		return 1;
	retval = count(subroot->left);
	retval = retval + count(subroot->right);
	return retval;
}


/**
 * Constructor to create an empty tree.
 */
template <typename T>
BinaryTree<T>::BinaryTree() : root(NULL) {
  /* nothing */
}

/**
 * Inserts into the BinaryTree, using BST insert algorithm.
 * @param elem The element to insert
 */
template <typename T>
void BinaryTree<T>::insert(const T& elem) {
  insert(root, elem);
}

template <typename T>
void BinaryTree<T>::insert(Node*& node, const T& elem)
{
    // If we're at a NULL pointer, we can put our element here
    if (node == NULL)
        node = new Node(elem);

    // Go left or right 
    else if (elem < node->elem)
        insert(node->left, elem);
    else
        insert(node->right, elem);
}
