#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

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
  imageinst = (png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  // So i create a copy of the image and now I need to traverse the image and put a new color onto the pixel; but that is performed in the next operartion
  // This function just focuses on storing the type of traversals and colorpicker and just provide that;
  traversal_type = & traversal;
  color_type = & colorPicker;
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
 * @param frameInterval how often to save frames of the animation
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  // So addfloodfill provides us with the type of traversal and which color to put into each pixel
  PNG tempimg = imageinst; 
  unsigned count = 0; // this count is to add the frame on every multiple of the frameinterval
  animation.addFrame(tempimg);
  for(auto itr = traversal_type->begin(); itr != traversal_type->end(); ++itr){
    count++;
    tempimg.getPixel((*itr).x, (*itr).y) = color_type->getColor((*itr).x, (*itr).y);
    if (count % frameInterval == 0){
        animation.addFrame(tempimg);
    }
  }
  animation.addFrame(tempimg);
  return animation;
}
