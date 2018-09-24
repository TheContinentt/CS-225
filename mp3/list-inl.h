/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
	if (head_ == NULL)
	{
		length_ = 0;
	}
	ListNode *temp = head_;
	ListNode *prv = NULL;
	while (temp != NULL)
	{
		prv = temp;
		temp = temp->next;
		delete prv;
		length_--;
	}
	//delete temp;
	//delete this;
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
	ListNode *temp = head_;
	ListNode *prv = NULL;
	while (temp != NULL)
	{
		prv = temp;
		temp = temp->next;
		delete prv;
		//length--;
	}
	delete temp;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
	if (head_ == NULL && tail_ == NULL)
	{
		ListNode *add = new ListNode(ndata);
		head_ = add;
		tail_ = add;
		length_ = 1;
	}
	else
	{
		ListNode *temp = head_;
		ListNode *add = new ListNode(ndata);
		add->next = head_;
		head_->prev = add;
		head_ = add;
		length_++;
	}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
	if (head_ == NULL && tail_ == NULL)
	{
		ListNode *add = new ListNode(ndata);
		head_ = add;
		tail_ = add;
		length_ = 1;
	}
	else
	{
		ListNode *add = new ListNode(ndata);
		ListNode *temp = tail_;
		tail_->next = add;
		add->prev = tail_;
		tail_ = add;
		length_++;
	}
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
	ListNode *temp;
	ListNode *t;
	ListNode *s = endPoint->next;
	//ListNode *store;
	/*temp = startPoint;
	startPoint = endPoint;
	endPoint = temp;*/
	temp = startPoint;
	while (temp != s)
	{
		//store = temp->next;
		t = temp->prev;
		temp->prev = temp->next;
		temp->next = t;
		temp = temp->prev;
	}
	/*t = temp->prev;
	temp->prev = temp->next;
	temp->next = t;*/
	temp = startPoint;
	startPoint = endPoint;
	endPoint = temp;
	temp = endPoint->next;
	endPoint->next = startPoint->prev;
	startPoint->prev = temp;
    /// @todo Graded in MP3.1
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
	if (n >= length_)
	{
		reverse(head_, tail_);
	}
	else
	{
		ListNode *tempp = head_;
		ListNode *end;
		ListNode *start = tempp;
		ListNode *tt;
		//ListNode *sss;
		int t = n;
		int flag = 1;
		int secondflag = 0;
		while (tempp != NULL)
		{
			while (t > 0 && tempp != NULL)
			{
				end = tempp;
				tempp = tempp->next;
				t--;
			}
			//tt = tempp;
			reverse(start, end);
			if (flag == 1)
			{
				head_ = start;
				flag = 0;
			}
			start = end->next;
			if (tempp != NULL)
			{
				tempp->prev = end;
				t = n - 1;
				while (t > 0 && tempp != NULL)
				{
					//pp = tempp;
					tt = tempp->next;
					//sss = tempp;
					if (tempp->next == NULL && t >= 1)
					{
						secondflag = 1;
						break;
					}
					tempp = tempp->next; /////////////
					t = t - 1;;
				}
				if (secondflag == 1)
				{
					end->next = tempp;
					//tempp = NULL;
				}
				else
				{	
					end->next = tt;
				}
			}
			else
			{
				end->next = NULL;
			}
			if (tempp == NULL)
			{
				break;
			}
			else
			{
				tempp = start;
				//start = end->next;
			t = n;
			}
		}
		
	}
	ListNode *tempp = head_;
	/*while (tempp != NULL)
	{
		cout << tempp->data << endl;
		tempp = tempp->next;
	}*/
  /// @todo Graded in MP3.1
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
	if (head_ == NULL)
	{
		return;
	}
	std::cout << head_->data<<std::endl;
	ListNode *temp = head_;
	ListNode *end = tail_;
	ListNode *pv;
	ListNode *nt;
	ListNode *store;
	while (temp->next != end)
	{
		pv = temp;
		nt = temp->next->next;
		store = temp->next;
		pv->next = nt;
		nt->prev = pv;
		end->next = store;
		store->prev = end;
		store->next = NULL;
		end = store;
		temp = temp->next;
	}
	/*ListNode *tempp = head_;
	while (tempp != NULL)
	{
		cout << tempp->data << endl;
		tempp = tempp->next;
	}*/	
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
	/*ListNode *tempp = ret.head_;
	while (tempp != NULL)
	{
		cout << tempp->data << endl;
		tempp = tempp->next;
	}*/
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
	if (start == NULL || splitPoint == 0)
	{
		return NULL;
	}
	ListNode *temp = start;
	ListNode *firstend = start;
	ListNode *newstart;
	ListNode *newend;
	int t = splitPoint - 1;
	while (t > 0)
	{
		temp = temp->next;
		t--;
	}
	firstend = temp;	
	newstart = temp->next;
	firstend->next = NULL;
	newstart->prev = NULL;
	return newstart;
    /// @todo Graded in MP3.2
    //return NULL;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

	/*ListNode *tempp = head_;
	while (tempp != NULL)
	{
		cout << tempp->data << endl;
		tempp = tempp->next;
	}*/
    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
	if (first == NULL && second != NULL)
	{
		return second;
	}
	else if (first != NULL && second == NULL)
	{
		return first;
	}
	else if (first == NULL && second == NULL)
	{
		return NULL;
	}
	else if (first == second)
	{
		return first;
	}
	else if (first->next == NULL && second->next == NULL)
	{
		if (second->data < first->data)
		{
			second->next = first;
			first->prev = second;
			return second;
		}
		else
		{
			first->next = second;
			second->prev = first;
			return first;
		}
	}
	else if (first->next == NULL && second->next->next == NULL)
	{
			if (second->data < first->data && first->data < second->next->data)
			{
				second->next->prev = first;
				first->prev = second;
				first->next = second->next;
				second->next = first;
				return second;
			}
			else if (first->data < second->data)
			{
				first->next = second;
				second->prev = first;
				return first;
			}
			else
			{
				second->next->next = first;
				first->prev = second->next;
				return second;
			}
	}
	else
	{
		ListNode *firsttemp = first->next;
		ListNode *pv = first;
		ListNode *secondtemp = second;
		ListNode *temp;
		while (secondtemp != NULL)
		{
			while (pv != NULL)
			{
				if (firsttemp == NULL)
				{
					pv->next = secondtemp;
					secondtemp->prev = pv;
					temp = secondtemp->next;
					secondtemp->next = NULL;
					firsttemp = NULL;
					pv = secondtemp;
					secondtemp = temp;
					break;
				}
				else if (secondtemp->data < first->data)
				{
					first->prev = secondtemp;
					temp = secondtemp->next;
					secondtemp->next = first;
					secondtemp->prev = NULL;
					first = secondtemp;
					pv = secondtemp;
					firsttemp = secondtemp->next;
					secondtemp = temp;
					break;
				}
				else if (secondtemp->data < firsttemp->data/* && pv->data < secondtemp->data*/)
				{
					temp = secondtemp->next;
					pv->next = secondtemp;
					firsttemp->prev = secondtemp;
					secondtemp->prev = pv;
					pv = secondtemp;
					secondtemp->next = firsttemp;
					//firsttemp = secondtemp;
					secondtemp = temp;
					break;
				}
				else
				{
					pv = firsttemp;
					firsttemp = firsttemp->next;
				}
			}
			//secondtemp = secondtemp->next;
			//pv = first;
			//firsttemp = first->next;
		}
		/*ListNode *tempp = first;
		while (tempp != NULL)
		{
			cout << tempp->data << endl;
			tempp = tempp->next;
		}*/
		return first;
	}
  //return NULL;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
	ListNode *tempp = head_;
	/*while (tempp != NULL)
	{
		cout << tempp->data << endl;
		tempp = tempp->next;
	}*/
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
	if (chainLength == 1 || chainLength == 0)
	{
		return start;
	}
	//ListNode newstart = split(chainLength/2);
	ListNode *t = start;
	int counter = chainLength/2;
	while (counter > 0)
	{
		t = t->next;
		counter--;
	}
	ListNode *temp = mergesort(t, chainLength - chainLength/2);
	ListNode *tempp = mergesort(start, chainLength/2);
	if (chainLength/2 == 1 && (chainLength - chainLength/2 == 1))
	{
		t->next = NULL;
		start->next = NULL;
		t->prev = NULL;
		start->prev = NULL;
	}
	else if (chainLength/2 == 1 && (chainLength - chainLength/2 != 1))
	{
		//t->next = NULL;
		start->next = NULL;
		t->prev = NULL;
		start->prev = NULL;
	}
	start = merge(tempp, temp);
	return start;
	//ListNode *t = mergesort(newstart, chainlength/2);
	
    //return NULL;
}
