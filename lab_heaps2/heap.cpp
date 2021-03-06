<<<<<<< HEAD

/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
	size_t retval = currentIdx * 2;
	return retval;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
	size_t retval = currentIdx * 2 + 1;
	return retval;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
	size_t retval = currentIdx / 2;
	return retval;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
	if (currentIdx * 2 >= _elems.size())
		return false;
	return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	if (hasAChild(currentIdx) == true)
	{
		/*if (2 * currentIdx == _elems.size())
			return 2 * currentIdx;*/
		if (2 * currentIdx + 1 == _elems.size())
		{
			return 2 * currentIdx;
		}
		if (higherPriority(_elems[2 * currentIdx], _elems[2 * currentIdx + 1]) == true)
			return 2 * currentIdx;
		return 2 * currentIdx + 1;
	}
	return 0;
//    return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
	if (currentIdx >= _elems.size())
        	return;
    	//size_t leftIdx = leftChild(currentIdx);
    	//size_t rightIdx = rightChild(currentIdx);
	size_t temp;
	temp = maxPriorityChild(currentIdx);
	if (temp == 0)
		return;
    	/*if (higherPriority(_elems[leftIdx], _elems[rightIdx]))
	{
		temp = leftIdx;
	}
	else
		temp = rightIdx;*/
	if (higherPriority(_elems[temp], _elems[currentIdx]) == true)
	{
        	std::swap(_elems[currentIdx], _elems[temp]);
        	heapifyDown(temp);
    	}
	/*else
	{
		std::swap(_elems[currentIdx], _elems[rightIdx]);
        	heapifyDown(rightIdx);
	}*/
	return;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
	_elems.push_back(T());
	index_ = 0;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
	_elems.push_back(T());
	index_ = 0;
	for (size_t i = 0; i < elems.size(); i++)
	{
		_elems.push_back(elems[i]);
		index_++;
	}
	//for (size_t j = 1; j < _elems.size(); j++)
	size_t end = parent(index_);
	for (size_t j = end; j > 0; j--)
	{
		heapifyDown(j);
	}
	/*for (size_t j = index_; j > end; j--)
	{
		heapifyUp(j);
	}*/
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
	if (index_ >= 1)
	{
		T retval = _elems[root()];
		std::swap(_elems[root()], _elems[index_]);
		_elems.pop_back();
		heapifyDown(root());
		index_--;
		return retval;
	}
	else
		return _elems[index_];
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems.back();

}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
	_elems.push_back(elem);
	index_++;
	heapifyUp(index_);
	return;
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
	//size_t retval = _elems.size();
	if (index_ == 0)
		return true;
	return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
=======

/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
	size_t retval = currentIdx * 2;
	return retval;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
	size_t retval = currentIdx * 2 + 1;
	return retval;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
	size_t retval = currentIdx / 2;
	return retval;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
	if (currentIdx * 2 >= _elems.size())
		return false;
	return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	if (hasAChild(currentIdx) == true)
	{
		/*if (2 * currentIdx == _elems.size())
			return 2 * currentIdx;*/
		if (2 * currentIdx + 1 == _elems.size())
		{
			return 2 * currentIdx;
		}
		if (higherPriority(_elems[2 * currentIdx], _elems[2 * currentIdx + 1]) == true)
			return 2 * currentIdx;
		return 2 * currentIdx + 1;
	}
	return 0;
//    return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
	if (currentIdx >= _elems.size())
        	return;
    	//size_t leftIdx = leftChild(currentIdx);
    	//size_t rightIdx = rightChild(currentIdx);
	size_t temp;
	temp = maxPriorityChild(currentIdx);
	if (temp == 0)
		return;
    	/*if (higherPriority(_elems[leftIdx], _elems[rightIdx]))
	{
		temp = leftIdx;
	}
	else
		temp = rightIdx;*/
	if (higherPriority(_elems[temp], _elems[currentIdx]) == true)
	{
        	std::swap(_elems[currentIdx], _elems[temp]);
        	heapifyDown(temp);
    	}
	/*else
	{
		std::swap(_elems[currentIdx], _elems[rightIdx]);
        	heapifyDown(rightIdx);
	}*/
	return;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
	_elems.push_back(T());
	index_ = 0;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
	_elems.push_back(T());
	index_ = 0;
	for (size_t i = 0; i < elems.size(); i++)
	{
		_elems.push_back(elems[i]);
		index_++;
	}
	//for (size_t j = 1; j < _elems.size(); j++)
	size_t end = parent(index_);
	for (size_t j = end; j > 0; j--)
	{
		heapifyDown(j);
	}
	/*for (size_t j = index_; j > end; j--)
	{
		heapifyUp(j);
	}*/
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
	if (index_ >= 1)
	{
		T retval = _elems[root()];
		std::swap(_elems[root()], _elems[index_]);
		_elems.pop_back();
		heapifyDown(root());
		index_--;
		return retval;
	}
	else
		return _elems[index_];
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems.back();

}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
	_elems.push_back(elem);
	index_++;
	heapifyUp(index_);
	return;
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
	//size_t retval = _elems.size();
	if (index_ == 0)
		return true;
	return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
>>>>>>> e73ee3ea7fbda9b3ac609f670b78729a8adece6d
