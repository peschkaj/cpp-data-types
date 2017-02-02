/* Jeremiah Peschka <jpeschka@pdx.edu>

   A templatized singly linked list class.

   The list manages all access to a linear linked list of nodes.

   T should implement the following:
   - operator=
   - copy constructor

   Access to the list is limited to a few basic functions:
   - first()/head()     - retrieves the head of the list.
   - last()/tail()      - retrieves the tail of the list.
   - head(list_node<T>) - Sets the head of the list
   - count()            - returns the count of nodes in the list
   - insert(T)          - adds to the beginning of the list
   - append(T)          - adds at the end of the list using the tail pointer
   - remove(T)          - removes all nodes that match the parameter
 */

#include "slist_node.h"
#include <exception>

#ifndef SLIST
#define SLIST

/* We're forward declaring the list_node... */
template <typename T>
class slist_node;

template <typename T>
class slist {
 public:
  /* Create a new list */
  slist();



  /* copy constructor */
  slist(const slist& rhs);



  /* Destroys this list
     Resources stored in each list node are also destroyed.
   */
  ~slist();



  /* Returns the first node of the list */
  slist_node<T>* first() const;



  /* Returns the first node of the list */
  slist_node<T>* head() const;



  /* Sets the head of the list to the new node
     This _replaces_ the existing head of the list, unlinks the old
     head, and removes the old head's contents.
   */
  void head(slist_node<T>* new_head);



  /* Returns the last node of the list */
  slist_node<T>* last();



  /* Returns the last node of the list */
  slist_node<T>* tail();



  /* Returns the count of items in the list */
  int count() const;



  /* Inserts a new item at the head of the list */
  bool insert(T const& to_add);



  /* Inserts a new item at the end of the list */
  bool append(T const& to_add);



  /* Deletes all occurrences of to_remove from the list.
     The number of nodes deleted is returned from the method.
   */
  int remove(const T& to_remove);



  /* Only removes the first occurrence of to_remove */
  bool remove_one(const T& to_remove);



  /* Converts this list into an array of T
     The array is returned via the `arr` parameter.
     Returns the number of elements in the array.
   */
  int to_array(T*& arr) const;



  /* Overloads operator= for an slist */
  slist operator=(const slist& rhs);

 private:
  /* A pointer to the head of the list */
  slist_node<T>* list_head;



  /* A pointer to the tail of the list */
  slist_node<T>* list_tail;



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
  slist_node<T>* remove(slist_node<T>* current, const T& to_remove,
                        int& removed);



  void remove_one(slist_node<T>* current, const T& to_remove, bool& removed);



  void copy_list(slist_node<T>* source);
};



/* Initializes an empty list
   head and tail are set to NULL
   the node count is set to 0
 */
template <typename T>
slist<T>::slist() : list_head(NULL), list_tail(NULL), node_count(0) {
}



template <typename T>
slist<T>::slist(const slist& rhs)
    : list_head(NULL), list_tail(NULL), node_count(0) {
  copy_list(rhs.list_head);
}



template <typename T>
void slist<T>::copy_list(slist_node<T>* source) {
  if (source == NULL) {
    return;
  }

  append(source->data());

  copy_list(source->next());
}



/* Destroys all resources managed by the list.
   The head node's destructor is called, this will cascade through all
   other nodes in the list and remove all data stored in the list.
   head and tail are set to NULL after the nodes of the list are destroyed
 */
template <typename T>
slist<T>::~slist() {
  if (list_head != NULL) {
    delete list_head;
  }
  list_head = NULL;
  list_tail = NULL;
}



/* Returns a pointer to the head of the list. */
template <typename T>
slist_node<T>* slist<T>::first() const {
  return head();
}



/* Returns a pointer to the head of the list. */
template <typename T>
slist_node<T>* slist<T>::head() const {
  return list_head;
}



/* Destroys the existing head pointer and replaces it with new_head */
template <typename T>
void slist<T>::head(slist_node<T>* new_head) {
  slist_node<T>* temp = list_head;
  list_head = new_head;

  if (temp != NULL) {
    list_head->next(temp->next());

    temp->next(NULL);
    delete temp;
  }
}



/* Returns a pointer to the last node in the list */
template <typename T>
slist_node<T>* slist<T>::last() {
  return tail();
}



/* Returns a pointer to the last node in the list */
template <typename T>
slist_node<T>* slist<T>::tail() {
  return list_tail;
}



/* Returns a count of the number of nodes in the list */
template <typename T>
int slist<T>::count() const {
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
bool slist<T>::insert(T const& to_add) {
  slist_node<T>* new_node = new slist_node<T>(to_add);

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
bool slist<T>::append(T const& to_add) {
  bool success = false;

  try {
    slist_node<T>* new_node = new slist_node<T>(to_add);

    if (list_tail == NULL) {
      list_head = new_node;
      list_tail = new_node;
    } else {
      list_tail->next(new_node);
      list_tail = new_node;
    }

    ++node_count;

    success = true;
  } catch (std::exception& e) {
    // do nothing, success is still false
  }

  return success;
}



/* Removes all occurrences of to_remove from the list.
   Returns the count of nodes removed.
 */
template <typename T>
int slist<T>::remove(const T& to_remove) {
  int removed = 0;

  list_head = remove(list_head, to_remove, removed);

  return removed;
}



/* Recursively removes all nodes from the list that match to_remove
   This assumes that T implements operator==
   **N.B.** If you need to use a list of char*, see `clist.h`
 */
template <typename T>
slist_node<T>* slist<T>::remove(slist_node<T>* current, const T& to_remove,
                                int& removed) {
  if (current == NULL) {
    return NULL;
  }

  current->next(remove(current->next(), to_remove, removed));

  if (current->next() == NULL && list_tail != current) {
    list_tail = current;
  }

  if (current->data() == to_remove) {
    slist_node<T>* temp = current;
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
bool slist<T>::remove_one(const T& to_remove) {
  bool removed = false;

  remove_one(list_head, to_remove, removed);

  return removed;
}



/* Recursive helper for `remove_one`.
   If the current node is NULL, return because this is the end of the list.
   Each node in the list is compared to `to_remove`, if the node matches
   (based on operator==) then the node is removed and removed is set to
   true.
   If the current node was not removed, the function recurs until either
    a) an element is removed
    b) the end of the list is encountered
 */
template <typename T>
void slist<T>::remove_one(slist_node<T>* current, const T& to_remove,
                          bool& removed) {
  slist_node<T>* temp;
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



/* Creates an array representation of this list.
   Returns the number of elements in the array. If the list is empty,
   0 is returned.
   The array representation of the list is passed by reference.
 */
template <typename T>
int slist<T>::to_array(T*& arr) const {
  slist_node<T>* current;

  if (list_head == NULL) {
    return 0;
  }

  arr = new T[node_count];
  current = list_head;

  for (int i = 0; i < node_count; ++i) {
    arr[i] = current->data();
    current = current->next();
  }

  return node_count;
}



/* Overload for operator= */
template <typename T>
slist<T> slist<T>::operator=(const slist<T>& rhs) {
  if (this == &rhs) {
    return *this;
  }

  slist_node<T>* current = rhs.head();

  while (current) {
    this->append(current->data());
    current = current->next();
  }

  return *this;
}
#endif
