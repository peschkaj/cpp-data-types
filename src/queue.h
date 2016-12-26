/* Jeremiah Peschka <jpeschka@pdx.edu>

   T should implement the following:
   - operator=
   - copy constructor

   A templatized queue. Provides the following operations:
    - enqueue(T item) - adds item at the beginning of the list
    - dequeue(T item) - removes the first item from the list
    - peek(T item)    - returns a copy of the first item in the list
    - is_empty()      - checks if the list is empty
 */

#include "slist.h"

#ifndef QUEUE
#define QUEUE

template <typename T>
class queue {
 public:
  /* Initializes the queue */
  queue<T>();



  /* Initializes the queue with another queue. */
  queue<T>(queue<T>& rhs);



  /* Destroys this queue and all managed resources. */
  ~queue<T>();



  /* Adds item to the beginning of the queue.

     Returns true if the item was added, false otherwise.
   */
  bool enqueue(T& item);



  /* Removes the first item from the queue.

     The item is is returned by reference.

     Returns true if an item is present in the queue, false otherwise.
   */
  bool dequeue(T& item);



  /* Peeks into the queue and returns the first item.

     Returns true if an item is present in the queue, false otherwise.

     The peek'd item is not removed from the queue.
   */
  bool peek(T& item);



  /* Checks if the queue is empty.

     Returns true if empty, false otherwise.
   */
  bool is_empty();
 private:
  /* The queue */
  slist<T>* q;
};



/* Initializes the queue and internal data structures. */
template <typename T>
queue<T>::queue() {
  // ummmm.... do something?
  q = new slist<T>;
}



/* Destroys this queue and associated resources */
template <typename T>
queue<T>::~queue() {
  delete q;
}



/* Adds `item` to the queue.

   Returns true if the item can be added to the queue, false otherwise.
 */
template <typename T>
bool queue<T>::enqueue(T& item) {
  return q->append(item);
}



/* Removes the first item from the queue.

   Returns true if an item is removed, false otherwise.

   The removed item is returned by reference in the `item` parameter.
 */
template <typename T>
bool queue<T>::dequeue(T& item) {
  bool success = peek(item);

  if (!success) {
    return success;
  }

  return q->remove_one(item);
}



/* Peeks into the queue and returns the first item.

   Returns false if the queue is empty, true otherwise.

   The peeked item is passed by reference in the `item` parameter.
 */
template <typename T>
bool queue<T>::peek(T& item) {
  if (is_empty()) {
    return false;
  }

  item = q->first()->data();

  return true;
}



/* Checks if the queue is empty.

   As the queue is backed by a list, this is handled by seeing if the
   list's count is equal to zero.
 */
template <typename T>
bool queue<T>::is_empty() {
  return (q->count() == 0);
}

#endif
