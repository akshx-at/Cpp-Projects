/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <cmath>//#include 'kdtree.h'
#include <iostream>
using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first, const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] == second[curDim]){
      return first<second;
     }
     else if((first[curDim] > second[curDim])){
        return false;
     }
     else{
      return true;
     }

}


template <int Dim>
bool shouldReplace(const Point<Dim>& target,const Point<Dim>& currentBest,const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
     double distance1 = 0;
     double distance2 = 0;
     // I have to calculate the mean sqare distance between two points compare those two distances and check which is one is greater and which one is smaller
     for(int i = 0; i < Dim; i++){
      distance1 += (target[i] - potential[i])*(target[i] - potential[i]);
      distance2 += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
     }
     if(distance1 == distance2){
      return potential<currentBest;
     }
     if(distance1 < distance2){
      return true;
     }
     else{ return false;}  
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::Createtree(vector<Point<Dim>>& newP,int left, int right, int dimensions)
{
  auto cmp=[dimensions](Point<Dim>left2, Point<Dim>right2){return smallerDimVal(left2,right2,dimensions);};
  if (left > right) {
    return NULL;
  }
  // cout<<left<<endl;
  // cout<<right<<endl;
  int median = (left + right ) / 2 ;
  //cout<<median<<endl;
  //cout<<"hui5"<<endl;
  //cout<<nodes<<endl;
  //cout<<"hui4"<<endl;
  auto iterstart = newP.begin() + left;
  auto iterend = newP.begin() + right + 1 ; 
  auto itermed = newP.begin() + median;

  // cout<<"The value of iterend"<<*iterend<<endl;
  // cout<<"The value of iter start"<<*iterstart<<endl;
  // cout<<"The value of itermid"<<*itermed<<endl;
  select(iterstart, iterend, itermed,cmp);

  typename KDTree<Dim>::KDTreeNode* nodes = new KDTreeNode(*itermed);
  // cout<<"after The value of iterend"<<*iterend<<endl;
  // cout<<"after The value of iter start"<<*iterstart<<endl;
  // cout<<"after The value of itermid"<<*itermed<<endl;
  // //cout<<"hui2"<<endl;
  dimensions++;
  nodes->left = Createtree(newP, left, median - 1, (dimensions) % Dim);
  nodes->right = Createtree(newP, median + 1, right , (dimensions) % Dim);
  size++;
  return nodes;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  if (newPoints.size() == 0) {
    // create an empty tree
    root = NULL;
    size = 0;
    return;
  }
  else { 
    vector<Point<Dim>> copypoints = newPoints;
    root = Createtree(copypoints,0, copypoints.size()-1,0);
    //int median2 = (copypoints.size() - 1) / 2;
    //cout<<median2<<endl;
    // int dim = 0;
    // auto cmp = [dim](Point<Dim> left2, Point<Dim> right2){return smallerDimVal(left2, right2, dim);}; 
    // auto iterstart2 = copypoints.begin();
    // auto iterend2 = copypoints.end(); 
    // auto itermed2 = copypoints.begin() + median2;
    // select(iterstart2, iterend2 , itermed2,cmp);
    // root = new KDTreeNode(*itermed2);
    // size = 1;
    // root->left = Createtree(copypoints, 0, median2 , (1) % Dim);
    // root->right = Createtree(copypoints, median2 + 1, copypoints.size()-1, (1) % Dim);
  }
  printTree(cout);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   size = other.size;
   root = copytree(other.root);

}
template <int Dim>
typename KDTree<Dim>::KDTreeNode *KDTree<Dim>::copytree(KDTreeNode* root){
  if(root == nullptr){
    return nullptr;
  }
  KDTreeNode* lhs = new KDTreeNode(root->point);
  lhs->left = copytree(root->left);
  lhs->right = copytree(root->right);
  return lhs;
 }

 template <int Dim>
 const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  if (this != &rhs) {  // check for self-assignment
    // delete current tree
    clear(root);
    size = 0;
    // create new tree as a copy of the rhs tree
    root = copytree(rhs.root);
    size = rhs.size;
  }
   return *this;
 }

 template <int Dim>
 KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   deletetree(root);

 }

 template <int Dim>
 void KDTree<Dim>::deletetree(KDTreeNode* root) {
  if(!root){
    return ;   
  }
  deletetree(root->left);
  deletetree(root->right);
  delete root; root = NULL;


 }

 template <int Dim>
 Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
 {
    /**
     * @todo Implement this function!
     */
      if(root == nullptr){
          return Point<Dim>();
        }

      Point<Dim> foundit =  helperNeighbor(query, 0, root);
      return foundit;
}

template <int Dim>
Point<Dim> KDTree<Dim>::helperNeighbor(const Point<Dim>& query,int dim,KDTreeNode* curRoot) const{
  Point<Dim> nearest = curRoot->point;
  Point<Dim> temp = curRoot->point;
  if (curRoot->left== NULL && curRoot->right == NULL){
    return curRoot->point; 
    // this conditiuon check if we have reached the end
    // we create a flag to keep a track if the nopdes have been visited ot not
  }
  bool visitedleft = false;
  bool othersubcheck = false;
  if (smallerDimVal(query, curRoot->point, dim)){
    if(curRoot->left != NULL)
    {
     // return curRoot->point;
     // we check this to make sure that after turning left the value isn't empty 
    nearest = helperNeighbor(query,(dim+1)% Dim,curRoot->left);// makes note of the closest node in to the potential node
    visitedleft = true;
  }
  else{return curRoot->point;}
  }
  else{
    if(curRoot->right != NULL){//return curRoot->point;
    nearest = helperNeighbor(query,(dim+1)% Dim,curRoot->right);// same as the previosu condition
  }
  else{return curRoot->point;}
  }
  // over here we kind of backtrace to check if the root value is closest or not 
  if (shouldReplace(query,nearest,curRoot->point)){
    nearest = curRoot->point;
  }
  //cout<< "Priniting nearest to check"<<nearest<<endl;
  double radius = 0.0;
  for (int i = 0; i < Dim; i++) {
	radius += (query[i] - nearest[i]) * (query[i] - nearest[i]);
}
  double distance = (curRoot->point[dim] - query[dim])*(curRoot->point[dim] - query[dim]);

  if(distance <= radius){
    if(visitedleft){
      if(curRoot->right){
     temp = helperNeighbor(query,(dim+1)% Dim,curRoot->right);
      //cout<<"Reached Right"<<endl;
      othersubcheck = true;
    }
    }
    else{
      if(curRoot->left){
      temp = helperNeighbor(query,(dim+1)% Dim,curRoot->left);
        //cout<<"Reached left"<<endl;
        othersubcheck = true;
    }
    }
    if(othersubcheck){
    if(shouldReplace(query,nearest, temp)){
      nearest = temp;
      //cout<<"Updated"<<endl;
    }
  }
  }
  //cout<<"Printing nearest to check if its value chnaged after backtracing"<<nearest<<endl;
  return nearest;
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */   
     //after we have partioned the list and we have achieved the left and right side of the pivot and also stored the pivot at the right position
     // we call the partition funtion
     RandIter newend = end - 1;
     if(end == start){return;}
     RandIter index = start;
    //  cout<<"The value of start in select"<<*start<<endl;
    //  cout<<"The value of end in select"<<*end<<endl;
    //  cout<<"The value of k in select"<<*k<<endl;
     index = (partition(start, newend, index, cmp));
     if(k == index){
      return;
     }
     else if(k < index){
    //cout<<"Met cond 1"<<endl;
      select(start,index,k,cmp);
    //      cout<<"The value of start in select"<<*start<<endl;
    //  cout<<"The value of end in select"<<*end<<endl;
    //  cout<<"The value of k in select"<<*k<<endl;
      return;
     }
     else{
      select(index + 1,end,k,cmp);
    //   cout<<"The value of start in select"<<*start<<endl;
    //  cout<<"The value of end in select"<<*end<<endl;
    //  cout<<"The value of k in select"<<*k<<endl;
      return;
     }  
}

//helper function to use in the quickselect algorithim
template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter val, Comparator cmp)
{
  // partition helper function will give us the value that is used as a pivot
  // This pivot varible will be used to divide the list into two piece
    auto pivotval = *val; 
    swap(*val,*(end)); // Move pivot to end
    RandIter storeIndex = start; // preserving this varible so it can be used to replace the value in the end
  for (RandIter iter = start; iter != end; ++iter){
    //cout<<"the value of the iterator is "<<*iter<<endl;
        if(cmp(*iter,pivotval)){
            iter_swap(storeIndex,iter);
            storeIndex++;
        }
  }
    std::iter_swap((end),storeIndex); // Move pivot to its final place
    return storeIndex;
}

