/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
 #include <iostream>

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  //so we delalocate the memory of the nodes or the linked list that we created in the previous functions
  ListNode* curr = head_;
  ListNode* temp;
  while(curr != NULL){
    temp = curr;
    curr = curr->next; 
    delete(temp);
  }
  length_ = 0;
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newnode = new ListNode(ndata);
  newnode->next = NULL;
  newnode->prev = tail_;

  if (tail_ != NULL) {
    tail_ -> next = newnode;
  }
  if (head_ == NULL) {
    head_ = newnode;
  }
  tail_=newnode;
  length_++;


}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;
// after the iteration, the pointer points to the value 
  if(splitPoint == 0 && start == head_){
    return head_;
  }
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  return curr;
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
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if(head_ == NULL && tail_ == NULL){
    return;
  }
    ListNode * curr = head_;
    int flag = 1;
    while(curr != tail_ && curr != NULL ){
      if(flag%2 == 0 && curr->next != NULL){
    //making temporary variables to store the values that will change
        ListNode * tempnext = curr->next;
        ListNode * temprev = curr->prev;
        ListNode * temp = curr->next;

        curr->prev->next = tempnext;
        curr->next->prev = temprev;

        tail_->next = curr;
        curr->next = NULL;
        curr->prev = tail_;
        tail_ = curr;

        curr = temp;
        }
      else{
        curr = curr->next;
      }
            flag++;
      }
}
/**
 * Reverses the current List.
 */
template <typename T>
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if(startPoint==NULL || endPoint == NULL || startPoint==endPoint){
    return;
  }
  ListNode* val1 = startPoint->prev;
  //std::cout <<"A"<<endl;
  ListNode* val2 = endPoint->next;
   //std::cout <<"A"<<endl;
  ListNode* curr = startPoint;
   //std::cout <<"A"<<endl;
  while(curr != val2 && curr!= NULL){
    ListNode* exchange = curr->next;
    curr->next = curr->prev;
    curr->prev = exchange;
    curr = curr->prev;
  }
   //std::cout <<"A"<<endl;
  startPoint->next = val2;
  if(val2 != NULL){
    val2->prev = startPoint;
  }
  endPoint->prev = val1;
  if(val1!= NULL){
    val1->next = endPoint;
  }
ListNode* replace = startPoint;
startPoint = endPoint;
endPoint = replace;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if(n >= length_ ) {
    reverse(head_, tail_);
    return; 
  }
  ListNode* start = head_; 
  ListNode* end = head_; 
  int counter = 0;  
  for(int i = 1; i <= length_; i++) {
    if(i % n == 0) {
      reverse(start, end);
      if(end == head_){
        head_ = start;
      }
      if(start == tail_) {
        tail_ = end;
      }
      start = end->next; 
      counter = i; 
    }
    end = end->next;
  }
  if (counter == length_) {
    return; 
  } else {
    reverse(start, tail_);
  } 
  tail_ = end; 
  return;   
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  if(first == nullptr && second == nullptr){
    return nullptr;
  }
  if(first == nullptr){
    return second;
  }
  if( second == nullptr){
    return first;
  }
  ListNode* head = nullptr;
  ListNode* added = nullptr;
  if (second->data < first->data){
    head = second;
    added = second;
    second = second->next; // should i check for null condition over here?
  }
  else{
    head = first;
    added = first;
    first = first->next; // same question; what if it's only 1 element long
  }
  while(first != nullptr && second != nullptr){
    if(first->data < second->data){
      ListNode* temp = added;
      added->next = first;
      added = first;
      added->prev = temp;
      first = first->next;
    }
    else{
      ListNode* temp = added;
      added->next = second;
      added = second;
      added->prev = temp;
      second = second->next;
    }
  }
  if (first != nullptr) {
    added->next = first;
    first->prev = added;
  }
  else 
  {
  added->next = second;
  second->prev = added;
  }
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if(chainLength == 1 || chainLength == 0){
    return start;
  }
  ListNode* split_1 = split(start,chainLength/2);
  ListNode* half1 = mergesort(start,chainLength/2);
  int len = chainLength - chainLength/2;
  ListNode* half2 = mergesort(split_1,len);
  ListNode* combine = merge(half1,half2);
  return combine;
}
