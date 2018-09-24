#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = png;
  size = 0;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
    //storeimage = traversal;
    //storecolor = colorPicker;
    /*HSLAPixel temp = getColor(traversal.current_.x, traversal.current_.y);
    HSLAPixel* temppixel = png.getPixel(traversal.current_.x, traversal.current_.y);
    *temppixel = temp;*/
    storeimage_.push_back(&traversal);// = &traversal;
    storecolor_.push_back(&colorPicker);// = &colorPicker;
    size++;
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  unsigned counter = frameInterval;
  HSLAPixel temp;
  HSLAPixel* temppixel;
  if (size == 1)
  {
  animation.addFrame(png_);
  //while (counter > 0)
  //{
ImageTraversal *tempimage = storeimage_.back();
  ColorPicker *tempcolor = storecolor_.back();
    for (ImageTraversal::Iterator it = tempimage->begin(); it != tempimage->end(); ++it)
    {
      temp = tempcolor->getColor(((*it).x), ((*it).y));
      temppixel = png_.getPixel(((*it).x), ((*it).y));
      *temppixel = temp;
      counter--;
      if (counter == 0){
        animation.addFrame(png_);
        counter = frameInterval;}
    }
    //if (counter != 0)
      //break;
    //animation.addFrame(png_);
    //counter = frameInterval;
  animation.addFrame(png_);
  return animation;
}
else if (size == 2)
{
    animation.addFrame(png_);
    //while (counter > 0)
    //{
    ImageTraversal *tempimage = storeimage_.back();
    ColorPicker *tempcolor = storecolor_.back();
      for (ImageTraversal::Iterator it = tempimage->begin(); it != tempimage->end(); ++it)
      {
        temp = tempcolor->getColor(((*it).x), ((*it).y));
        temppixel = png_.getPixel(((*it).x), ((*it).y));
        *temppixel = temp;
        counter--;
        if (counter == 0){
          animation.addFrame(png_);
          counter = frameInterval;}
      }
      animation.addFrame(png_);
      counter = frameInterval;
      tempimage = storeimage_.front();
      tempcolor = storecolor_.front();
      animation.addFrame(png_);
        for (ImageTraversal::Iterator it = tempimage->begin(); it != tempimage->end(); ++it)
        {
          temp = tempcolor->getColor(((*it).x), ((*it).y));
          temppixel = png_.getPixel(((*it).x), ((*it).y));
          *temppixel = temp;
          counter--;
          if (counter == 0){
            animation.addFrame(png_);
            counter = frameInterval;}
        }

      //if (counter != 0)
        //break;
      //animation.addFrame(png_);
      //counter = frameInterval;
    animation.addFrame(png_);
    return animation;
  }
      return animation;
}
