/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

/* smallerDimVal;
 * Description: This function compares one specific dimension coordination of two input points.
 * Input: first: The first input pointer to be compared.
 * 	  second: The second input pointer to be compared.
 *	  curDim: the dimension of point that we want to compare.
 * Output: none.
 * Return Value: retval: the result we get from comparison.
 * SideEffect: none.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	if (first[curDim] <= second[curDim])
		return true;
    	return false;
}

/* shouldReplace;
 * Description: This function compares two points' distance to a target point.
 * Input: target: The targer pointer which we calculate distance to it.
 * 	  currentBest: The current best point that is closest to target point.
 *	  potential: the point we want to chech whether it's close to target than currentBest.
 * Output: none.
 * Return Value: retval: the result we get from comparison.
 * SideEffect: none.
 */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	int number = Dim - 1;
	int counter = 0;
	double suma = 0;
	double sumb = 0;
	while (counter < Dim)
	{
		suma += pow((target[counter] - currentBest[counter]), 2);
		sumb += pow((target[counter] - potential[counter]), 2);
		counter++;
	}
	if (sumb < suma)
		return true;
	else if (sumb == suma)
		return potential < currentBest;
	else
	    	return false;
}

/* KDTree;
 * Description: The constuctor of kdtree according to an input vector of point.
 * Input: newPoints: the vector of point that include data of kdtree nodes.
 * Output: none.
 * Return Value: none.
 * SideEffect: none.
 */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	int size;
	points = newPoints;
	size = points.size();
	KDTreehelper(0, size - 1, 0);
}

/* KDTreehelper;
 * Description: The helper function of KD tree constructor.
 * Input: left: the left index of the vector.
 *	  right: the right index of the vector.
 *	  dimension: the dimension of point that we sorted by.
 * Output: none.
 * Return Value: none.
 * SideEffect: none.
 */
template <int Dim>
void KDTree<Dim>::KDTreehelper(int left, int right, int dimension)
{
    /**
     * @todo Implement this function!
     */
	if (left >= right)
		return;
	int middle = (left + right) / 2;
	Quickselect(left, right, middle, dimension);
	if (left < middle)
		KDTreehelper(left, middle - 1, (dimension + 1) % Dim);
	if (right > middle)
		KDTreehelper(middle + 1, right, (dimension + 1) % Dim);
		
}

/* Partition;
 * Description: The helper function to quicksort current vector.
 * Input: left: the left index of the vector.
 *	  right: the right index of the vector.
 *	  middleindex: the middle index of the vector.
 *	  dimension: the dimension of point that we sorted by.
 * Output: none.
 * Return Value: retval: the indecx of the median point.
 * SideEffect: none.
 */
template <int Dim>
int KDTree<Dim>::Partition(int left, int right, int middleindex, int dimension)
{
	Point<Dim> temp;
	temp = points[middleindex];
	std::swap(points[middleindex], points[right]);
	int store = left;
	int i = left;
	for (i = left; i < right; i++)
	{
		if (smallerDimVal(points[i], temp, dimension) == true)
		{
			std::swap(points[store], points[i]);
			store++;
		}
	}
	std::swap(points[right], points[store]);
	return store;
}

/* Quickselect;
 * Description: The helper function to quickselect median of the current vector.
 * Input: left: the left index of the vector.
 *	  right: the right index of the vector.
 *	  middle: the middle index of the vector.
 *	  dimension: the dimension of point that we sorted by.
 * Output: none.
 * Return Value: retval: the midian point of the input vector.
 * SideEffect: none.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::Quickselect(int left, int right, int middle, int dimension)
{
	if(left >= right)
	        return Point<Dim>();
	int retval = Partition(left, right, middle, dimension);
	if (retval == middle)
	{
		return points[retval];
	}
	else if (middle < retval)
	{
		return Quickselect(left, retval - 1, middle, dimension);
	}
	else
	{
		return Quickselect(retval + 1, right, middle, dimension);
	}
}

/* findNearestNeighbor;
 * Description: The function used to find the nearest point to our input point.
 * Input: query: the given point that we want to find its nearest neighbor.
 * Output: none.
 * Return Value: retval: the nearest point of the input point.
 * SideEffect: none.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
	int size = points.size();
	int middle = (size - 1) / 2;
	Point<Dim> retval;
	retval = findNearestNeighborhelper(query, 0, size - 1, middle, 0);
	return retval;
}

/* findNearestNeighborhelper;
 * Description: The function used to find the nearest point to our input point.
 * Input: query: the given point that we want to find its nearest neighbor.
 *	  left: the left index of the vector.
 *	  right: the right index of the vector.
 *	  middle: the middle index of the vector.
 *	  dimension: the dimension of point that we sorted by.
 * Output: none.
 * Return Value: retval: the nearest point of the input point.
 * SideEffect: none.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborhelper(const Point<Dim>& query, int left, int right, int middle, int dimension) const
{
    /**
     * @todo Implement this function!
     */
	Point<Dim> retval;
	Point<Dim> compare;
	Point<Dim> third;
	int tempmiddle;
	if (right < left)
		return Point<Dim>();
	if (right == left)
	{
		return points[left];
	}
	if (smallerDimVal(query, points[middle], dimension) == true)
	{
		tempmiddle = (left + middle - 1) / 2;
		retval = findNearestNeighborhelper(query, left, middle - 1, tempmiddle, (dimension + 1) % Dim);
	}
	tempmiddle = (right + middle + 1) / 2;
	compare = findNearestNeighborhelper(query, middle + 1, right, tempmiddle, (dimension + 1) % Dim);
	if (shouldReplace(query, retval, compare) == true){
		retval = compare;
	}
	tempmiddle = (left + middle - 1) / 2;
	third = findNearestNeighborhelper(query, left, middle - 1, tempmiddle, (dimension + 1) % Dim);
	if (shouldReplace(query, retval, third) == true){
		retval = third;
	}
	if (shouldReplace(query, retval, points[middle]) == true)
	{
		retval = points[middle];
	}
	return retval;
}

