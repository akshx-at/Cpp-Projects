#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    // bfs implements a queue because BFS works on the implementation of FIFO(First in First out)
    // BFS adds each element in the row onto the queue before moving to the next row
    // so while removing elements from the queue, we remove the first element on the queue currently

    work_list.push_back(point);
    // We push the elements to the end of the list
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    // DFS works like vectors, which works on the implementation of the LIFO(Last in First Out)
    // while adding, we add values to the end of the vectors

    work_list.push_back(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //we pop the first element of the list every time;
    Point val = work_list.front();
    work_list.pop_front();
    return val;
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    // we pop the element from the last everytime;
    //return Point(0, 0);
    Point val = work_list.back();
    work_list.pop_back();
    return val;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
    /** @todo [Part 1] */
    picture = png;
    startpoint = start;
    toleranceval = tolerance;
    add1 = traversal_add;
    pop1 = traversal_pop;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    // begin() should return the first object of the iterator
    // begin should always the first point passed in as start in the Image traversal object 
    Iterator myIt(picture, startpoint, toleranceval, add1, pop1);
    return myIt;
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    Iterator enditr;
    return enditr;

  }

  ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {
    picture = png;
    startpoint = start;
    toleranceval = tolerance;
    add1 = traversal_add;
    pop1 = traversal_pop;
    curr = start;
    visited_list.resize(picture.width(), std::vector<int>(picture.height(),0));
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    curr = Point(1000,1000);
  }


  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    //the operator++ makes sure to increment the value of the iterator and return the next value in the iterator
    //we check what the curr point is pointing to. Initially I will assign it to the starting point and push that value onto the visted stack, and check its right,down,left,up values and if they exist push that onto the dequeue
    //get the value of the neighbors
    
    //add1(visited_list[curr.x()][curr.y()],curr); // this will add the vlaue on to the visited section
    visited_list[curr.x][curr.y] = 1;
    Point Right = Point(curr.x + 1,curr.y);
    if(ValidPoint(Right)){
      //if the list is valid push the point onto the stack
      add1(work_list,Right);
    }
    Point Bottom = Point(curr.x,curr.y+1);
        if(ValidPoint(Bottom)){
      //if the list is valid push the point onto the stack
      add1(work_list,Bottom);
    }
    Point Left = Point(curr.x-1,curr.y);
        if(ValidPoint(Left)){
      //if the list is valid push the point onto the stack
      add1(work_list,Left);
    }
    Point Up =  Point(curr.x,curr.y-1);
        if(ValidPoint(Up)){
      //if the list is valid push the point onto the stack
      add1(work_list,Up);
    }
  
    // We have added the points onto the stack if they are valid

    // once we have done this we pop the value and add that value onto the visited list so that we dont visit it again

    while((Invisitedlist(curr))){
    if(work_list.size() == 0){
      curr = Point(1000,1000);
      return *this;
    }
    else{
      // Point key = visited_list.back();
      // if (!(Invisitedlist(key))){
        Point poppedval = pop1(work_list);
        curr = poppedval;        
    }    
    }
      return *this;
  }

 bool ImageTraversal::Iterator::Invisitedlist(Point & point1){
  //  bool flag2 = false;
  //   for (auto itr2 = visited_list.begin(); itr2 != visited_list.end(); itr2++){
  //     if (point1 == *itr2){
  //      flag2 = true;
  //     }
  //   }
  //     return flag2;
      if(visited_list[point1.x][point1.y] == 1){
        return true;
      }
      else{
        return false;
      }
 }

  bool ImageTraversal::Iterator::ValidPoint(Point & point1){

    //So a point is considered valid is: 1) the x and y index are in bounds 
    //                                   2) It is within the tolerance level
    //                                   3) if its not the visted_list 
    // if any of these conditions are true then the returns false 
    // bool flag = true;
    // // bool flag2 = true;
    // for (auto itr = visited_list.begin(); itr != visited_list.end(); itr++){
    //   if (point1 == *itr){
    //     flag = false;
    //   }
    // }

    // for (auto itr2 = work_list.begin(); itr2 != work_list.end(); itr2++){
    //   if (point1 == *itr2){
    //     flag2 = false;
    //   }
    // }

    if(point1.x >= picture.width() || point1.y >= picture.height() || point1.x < 0 || point1.y < 0 ){
      return false;
    }

    else if((calculateDelta(picture.getPixel(point1.x, point1.y),picture.getPixel(startpoint.x, startpoint.y)) < toleranceval)){
      return true;
    }
    else{
      return false;
    }
  }

  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return curr;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return !(curr == other.curr);
  }

}