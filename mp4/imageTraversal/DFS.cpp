#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

using namespace cs225;
/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
	store_ = png.getPixel(start.x, start.y);
	tolerance_ = tolerance;
	size_ = 1;
	start_ = start;
	png_ = png;
	iteratorstack.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
	Iterator* a = new Iterator(this, png_, start_, tolerance_);
  return *a;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
	//ImageTraversal::Iterator() = &end_;
	//Iterator *a = Iterator();
  return ImageTraversal::Iterator();
}


/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
		iteratorstack.push(point);
		size_++;
		return;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
	Point temp = iteratorstack.top();
	iteratorstack.pop();
	size_--;
	return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
	Point temp = iteratorstack.top();
	return temp;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
	if (size_ == 0)
		return true;
	return false;
}
