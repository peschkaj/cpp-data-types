/* Jeremiah Peschka <jpeschka@pdx.edu>

   A templatized list class.

   The list manages all access to a linear linked list of nodes.

   Access to the list is limited to a few basic functions:
   - first()/head()     - retrieves the head of the list.
   - last()/tail()      - retrieves the tail of the list.
   - head(list_node<T>) - Sets the head of the list
   - count()            - returns the count of nodes in the list
   - insert(T)          - adds to the beginning of the list
   - append(T)          - adds at the end of the list using the tail pointer
   - remove(T)          - removes all nodes that match the parameter
 */

#include "list_node.h"

#ifndef LIST
#define LIST

template<typename T>
class list {
 public:
  /* Create a new list */
  list();



  /* Destroys this list

     Resources stored in each list node are also destroyed.
   */
  ~list();



  /* Returns the first node of the list */
  list_node<T>* first();



  /* Returns the first node of the list */
  list_node<T>* head();



  /* Sets the head of the list to the new node

     This _replaces_ the existing head of the list, unlinks the old
     head, and removes the old head's contents.
   */
  void head(list_node<T>* new_head);



  /* Returns the last node of the list */
  list_node<T>* last();



  /* Returns the last node of the list */
  list_node<T>* tail();



  /* Returns the count of items in the list */
  int count() const;



  /* Inserts a new item at the head of the list */
  bool insert(T to_add);



  /* Inserts a new item at the end of the list */
  bool append(T to_add);



  /* Deletes all occurrences of to_remove from the list.

     The number of nodes deleted is returned from the method.
   */
  int remove(const T& to_remove);



  /* Only removes the first occurrence of to_remove */
  bool remove_one(const T& to_remove);
 private:
  /* A pointer to the head of the list */
  list_node<T>* list_head;



  /* A pointer to the tail of the list */
  list_node<T>* list_tail;



  /* The current node count in the list */
  int node_count;



  /* Removes a node from the list

     Recursively deletes from the list. This requires a full traversal
     of the list. The tail of the list will be properly maintained through
     all operations on the list.

     Inputs:
     - current   - the current node to operate on
     - to_remove - the T to match for removal. This requires that T implement
                   the == operator.
     - removed   - the count of nodes removed

     Outputs:
     The next node in the list, after removal.
   */
  list_node<T>* remove(list_node<T>* current, const T& to_remove, int& removed);



  void remove_one(list_node<T>* current, const T& to_remove, bool& removed);
};



/* Initializes an empty list

   head and tail are set to NULL
   the node count is set to 0
 */
template <typename T>
list<T>::list() {
  list_head = NULL;
  list_tail = NULL;
  node_count = 0;
}



/* Destroys all resources managed by the list.

   The head node's destructor is called, this will cascade through all
   other nodes in the list and remove all data stored in the list.

   head and tail are set to NULL after the nodes of the list are destroyed
 */
template <typename T>
list<T>::~list() {
  delete list_head;
  list_head = NULL;
  list_tail = NULL;
}



/* Returns a pointer to the head of the list. */
template <typename T>
list_node<T>* list<T>::first() {
  return head();
}



/* Returns a pointer to the head of the list. */
template <typename T>
list_node<T>* list<T>::head() {
  return list_head;
}



/* Destroys the existing head pointer and replaces it with new_head */
template <typename T>
void list<T>::head(list_node<T>* new_head) {
  list_node<T>* temp = list_head;
  list_head = new_head;

  if (temp != NULL) {
    list_head->next(temp->next());

    temp->next(NULL);
    delete temp;
  }
}



/* Returns a pointer to the last node in the list */
template <typename T>
list_node<T>* list<T>::last() {
  return tail();
}



/* Returns a pointer to the last node in the list */
template <typename T>
list_node<T>* list<T>::tail() {
  return list_tail;
}



/* Returns a count of the number of nodes in the list */
template <typename T>
int list<T>::count() const {
  return node_count;
}



/* Adds a new node at the head of the list.

   Returns true if the addition was successful, false otherwise.

   Because of the order of operations, a failure to allocate additional
   memory will have no other ill effects - the method call will fail,
   but there's no need to create a temporary pointer for the head of
   the list.
 */
template <typename T>
bool list<T>::insert(T to_add) {
  list_node<T>* new_node = new list_node<T>(to_add);

  if (list_head == NULL) {
    list_tail = new_node;
  }

  new_node->next(list_head);
  list_head = new_node;
  ++node_count;

  return true;
}



/* Adds a new node at the end of the list. */
template <typename T>
bool list<T>::append(T to_add) {
  list_node<T>* new_node = new list_node<T>(to_add);

  if (list_tail == NULL) {
    list_head = new_node;
    list_tail = new_node;
  } else {
    list_tail->next(new_node);
    list_tail = new_node;
  }

  ++node_count;

  return true;
}



/* Removes all occurrences of to_remove from the list.

   Returns the count of nodes removed.
 */
template <typename T>
int list<T>::remove(const T& to_remove) {
  int removed = 0;

  list_head = remove(list_head, to_remove, removed);

  return removed;
}



/* Recursively removes all nodes from the list that match to_remove

   This assumes that T implements operator==

   **N.B.** If you need to use a list of char*, see `clist.h`
 */
template <typename T>
list_node<T>* list<T>::remove(list_node<T>* current,
                              const T& to_remove,
                              int& removed) {
  if (current == NULL) {
    return NULL;
  }

  current->next(remove(current->next(),
                       to_remove,
                       removed));

  if (current->next() == NULL && list_tail != current) {
    list_tail = current;
  }

  if (current->data() == to_remove) {
    list_node<T>* temp = current;
    current = current->next();

    temp->next(NULL);
    delete temp;
    temp = NULL;

    --node_count;
    ++removed;
  }

  return current;
}



/* Removes the first occurrence of to_remove */
template <typename T>
bool list<T>::remove_one(const T &to_remove) {
  bool removed = false;

  remove_one(list_head, to_remove, removed);

  return removed;
}


template <typename T>
void list<T>::remove_one(list_node<T>* current, const T& to_remove, bool& removed) {
  list_node<T>* temp;
  if (current == NULL) {
    return;
  }

  if (current->data() == to_remove) {
    temp = current;

    if (current == list_head) {
      list_head = current->next();
    }

    if (current == list_tail) {
      list_tail = list_head;
    }

    current = current->next();
    temp->next(NULL);
    delete temp;

    removed = true;
  }

  if (!removed) {
    remove_one(current->next(), to_remove, removed);
  }
}
#endif
