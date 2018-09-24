#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */

ImageTraversal::Iterator::Iterator(ImageTraversal* IT, PNG & png, Point & start, double tolerance) {
  /** @todo [Part 1] */
	traversal_ = IT;
	png_ = png;
	start_ = start;
	tolerance_ = tolerance;
	current_ = start_;
  	check = new int*[png_.width()];
	for(unsigned int i = 0; i < png_.width(); ++i)
	{
		check[i] = new int[png_.height()];
	}
	unsigned int j = 0;
	unsigned int i = 0;
	while (i < png_.width())
	{
	    while (j < png_.height())
	    {
	      	check[i][j] = 0;
   	   	j++;
   	     }
   	 j = 0;
   	 i++;
  	}
  	check[start.x][start.y] = -1;
  	store_ = png.getPixel(start.x, start.y);
  	flag = false;
}

ImageTraversal::Iterator::Iterator() {
  flag = true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  	HSLAPixel* temp;
	double difference_;
  	current_ = traversal_->pop();
  //  check[current_.x][current_.y] = -1;//////////////
	if (current_.x < png_.width() - 1 && check[current_.x + 1][current_.y] == 0)
	{
		temp = png_.getPixel(current_.x + 1, current_.y);
		difference_ = calculateDelta(*temp, *store_);
		if (difference_ < tolerance_)
		{
			this->traversal_->add(Point(current_.x + 1, current_.y));
      			check[current_.x + 1][current_.y] = -1;
		}
	}
	if (current_.y < png_.height() - 1 && check[current_.x][current_.y + 1] == 0)
	{
		temp = png_.getPixel(current_.x, current_.y + 1);
		difference_ = calculateDelta(*temp, *store_);
		if (difference_ < tolerance_)
		{
			this->traversal_->add(Point(current_.x, current_.y + 1));
		        check[current_.x][current_.y + 1] = -1;
		}
	}
	if (current_.x > 0 && check[current_.x - 1][current_.y] == 0)
	{
		temp = png_.getPixel(current_.x - 1, current_.y);
		difference_ = calculateDelta(*temp, *store_);
		if (difference_ < tolerance_)
		{
			this->traversal_->add(Point(current_.x - 1, current_.y));
		        check[current_.x - 1][current_.y] = -1;
		}
	}
	if (current_.y > 0 && check[current_.x][current_.y - 1] == 0)
	{
		temp = png_.getPixel(current_.x, current_.y - 1);
		difference_ = calculateDelta(*temp, *store_);
		if (difference_ < tolerance_)
		{
			this->traversal_->add(Point(current_.x, current_.y - 1));
      			check[current_.x][current_.y - 1] = -1;
		}
	}
	if (traversal_->empty() == true)
  	{
  		flag = true;
      for(unsigned int i = 0; i < png_.width(); ++i) {
        delete[] check[i];
    }
		return *this;
 	}
  //current_ = traversal_->pop();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
	Point m = traversal_->peek();
  return m;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
	/*double a = this->tolerance_;
	double b = other.tolerance_;
	bool retval = true;
	if (a == b)
		retval = false;*/
	if (flag == true)
		return false;
  	return true;
}
