/* Jeremiah Peschka <jpeschka@pdx.edu>

   T should implement the following:
   - operator=
   - copy constructor

   A templatized stack. Provides the following operations:
    - enstack(T item) - adds item at the beginning of the list
    - destack(T item) - removes the first item from the list
    - peek(T item)    - returns a copy of the first item in the list
    - is_empty()      - checks if the list is empty
 */

#include "slist.h"

#ifndef STACK
#define STACK

template <typename T>
class stack {
 public:
  /* Initializes the stack */
  stack<T>();



  /* Initializes the stack with another stack. */
  stack<T>(stack<T>& rhs);



  /* Destroys this stack and all managed resources. */
  ~stack<T>();



  /* Adds item to the beginning of the stack.

     Returns true if the item was added, false otherwise.
   */
  bool push(const T& item);



  /* Removes the first item from the stack.

     The item is is returned by reference.

     Returns true if an item is present in the stack, false otherwise.
   */
  bool pop(T& item);



  /* Peeks into the stack and returns the first item.

     Returns true if an item is present in the stack, false otherwise.

     The peek'd item is not removed from the stack.
   */
  bool peek(T& item);



  /* Checks if the stack is empty.

     Returns true if empty, false otherwise.
   */
  bool is_empty();
 private:
  /* The stack */
  slist<T> q;
};



/* Initializes the stack and internal data structures. */
template <typename T>
stack<T>::stack() {

}



/* Destroys this stack and associated resources */
template <typename T>
stack<T>::~stack() {

}



/* Adds `item` to the stack.

   Returns true if the item can be added to the stack, false otherwise.
 */
template <typename T>
bool stack<T>::push(const T& item) {
  return q.insert(item);
}



/* Removes the first item from the stack.

   Returns true if an item is removed, false otherwise.

   The removed item is returned by reference in the `item` parameter.
 */
template <typename T>
bool stack<T>::pop(T& item) {
  bool success = peek(item);

  if (!success) {
    return success;
  }

  return q.remove_one(item);
}



/* Peeks into the stack and returns the first item.

   Returns false if the stack is empty, true otherwise.

   The peeked item is passed by reference in the `item` parameter.
 */
template <typename T>
bool stack<T>::peek(T& item) {
  if (is_empty()) {
    return false;
  }

  item = q.first()->data();

  return true;
}



/* Checks if the stack is empty.

   As the stack is backed by a list, this is handled by seeing if the
   list's count is equal to zero.
 */
template <typename T>
bool stack<T>::is_empty() {
  return (q.count() == 0);
}

#endif
