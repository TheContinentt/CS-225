/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	mirror(root);
    //your code here
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
	if (subRoot == NULL)
		return;
	//mirror(subRoot->left);
	Node *temp;
	temp = subRoot->right;
	subRoot->right = subRoot->left;
	subRoot->left = temp;
	mirror(subRoot->left);
	mirror(subRoot->right);
	return;
}


/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
	bool retval = isOrdered(root);
	return retval;
    //return false;
}

template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const
{
	bool retval = true;;
	
	if (subRoot == NULL)
		return true;
	if (subRoot->left != NULL)
	{
		retval = retval && isOrdered(subRoot->left);
		if (subRoot->left->elem >= subRoot->elem)
		{
			return false;
		}
	}
	if (subRoot->right != NULL)
	{
		retval = retval && isOrdered(subRoot->right);
		if (subRoot->right->elem <= subRoot->elem)
		{
			return false;
		}
	}
	/*retval = retval && isOrdered(root->left) && isOrdered(root->right);
	if (root->left == NULL && root->right == NULL)
		return true;*/
	return retval;
	
	



}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
	T i = 0;
	vector<T> temp;
	//temp.push_back(1);
	//paths[i].push_back(root->elem);
	//paths.push_back(temp);
	printPaths(paths, root, i, temp);
    // your code here
}

template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths, Node* subRoot, T i, vector<T> temp) const
{
	if (subRoot == NULL)
		return;
	temp.push_back(subRoot->elem);
	//if (subRoot->left != NULL)
	//{
	if (subRoot->left == NULL && subRoot->right == NULL)
	{
		//temp.push_back(subRoot->elem);
		paths.push_back(temp);
		temp.pop_back();
	}
		printPaths(paths, subRoot->left, i, temp);
		//paths.push_back(temp);
	//}
	if (subRoot->right != NULL)
	{
		//temp.pop_back();
		printPaths(paths, subRoot->right, i, temp);
		//paths.push_back(temp);
		//temp.clear();
	}
	
	 
}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
	int i = -1;
	int retval = sumDistances(root, i);
    	return retval;
}

template <typename T>
int BinaryTree<T>::sumDistances(Node *subRoot, int i) const
{
	int retval = 0;
	if (subRoot == NULL)
		return 0;
	i++;
	/*if (subRoot->left == NULL && subRoot->right == NULL)
	{
		//temp.push_back(subRoot->elem);
		retval = i;
		i--;
	}*/
	retval = retval + i + sumDistances(subRoot->left, i);
	if (subRoot->right != NULL)
	{
		//temp.pop_back();
		retval = retval + sumDistances(subRoot->right, i);
		//paths.push_back(temp);
		//temp.clear();
	}
	return retval;
}
