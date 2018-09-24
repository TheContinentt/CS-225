/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
	if (s.empty() == 1)
	{
		return T();//T();
	}
	else
	{
		//stack<T> ss = s;
		double temp = s.top();
		s.pop();
		double ret = temp + sum(s);
		s.push(temp);
		return ret;
	}
    // Your code here
	//if ()
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
	queue<T> same;
    // optional: queue<T> q2;
	int loop = 1;
	int reversenumber = 2;
	int size = q.size();
	int flag = 0;
	int temp;
	int loopconstant = 1;
	int t;
	while (q.empty() == 0)
	{
		if (loop <= 0)
		{
			flag = 1;
			temp = reversenumber;
			if (size < reversenumber)
			{
				temp = size;
			}
			while (temp > 0)
			{
				t = q.front();
				s.push(t);
				q.pop();
				temp--;
			}
			temp = reversenumber;
			if (size < reversenumber)
			{
				temp = size;
			}
			while (temp > 0)
			{
				t = s.top();
				same.push(t);
				s.pop();
				temp--;
				size--;
			}
			reversenumber = reversenumber + 2;
			loop = loopconstant + 2;
			loopconstant = loopconstant + 2;
			flag = 0;
			continue;
		}
		temp = q.front();
		same.push(temp);
		q.pop();
		loop--;
		size = size - 1;
	}
	while (same.empty() == 0)
	{
		int tt = same.front();
		q.push(tt);
		same.pop();
	}
		
    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
        bool retval = true; //set default boolean return value to true
	if (s.empty() == 1) //check if stack reaches the end, if true, we could start to compare queue with stack
	{
		return true; //return true in order to tell program to compare
	}
	T curs = s.top(); //store the top value of stack in T type l.v. named curs
	s.pop(); //remove the top element
	retval = verifySame(s, q); //by recursion we continuously remove and store the elements in stack in an opposite sequence to the original stack pop sequence. So stack and queue elements are in the same sequences and thus the program could start to check whether elements are same or not.
	T curq = q.front(); //store the top element in queue to T type l.v. curq for the later comparison
	q.push(curq); //push this top element back to queue so after a cycle of comparison, the queue would change back to what it should be before comparison with stack elements
	q.pop(); //remove this top element in order to read next element by recursion calling.
	retval = ((curs == curq) && retval); // check if the previous result and this layer of recursion is true or not. If at least one of them are false, the return value would never be change to true anymore.
	s.push(curs); //push back the element stored in curs to stack in its original sequence to satisfy the test requirement.
    return retval; //return the result of this layer and lower layers recursion. If there's no more recursion are called, it returns boolean value to the function where it's called.
}

}
