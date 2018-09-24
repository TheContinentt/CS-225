#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
	Point current_;
	PNG png_;
	std::stack<Point> iteratorstack;
	int size_;
	double tolerance_;
	HSLAPixel* store_;
	Point start_;

private:
	//std::queue<Point> DFSstore;
	//std::queue *head_;
	//std::queue *tail_;
	//int size_;
	//double tolerance_;
	//HSLAPixel* store_;
	//Point start_;
	//Point end_;
};

#endif
