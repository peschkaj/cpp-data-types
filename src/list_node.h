/* Jeremiah Peschka <jpeschka@pdx.edu>

   A templatized doubly linked list node.

   T should implement the following:
   - operator=
   - copy constructor
 */

#include <exception>
#include <iostream>

#ifndef LIST_NODE
#define LIST_NODE

template <typename T>
class list_node {
 public:
  list_node();
  list_node(const list_node& rhs);
  list_node(const T data);
  ~list_node();

  list_node* next() const;
  void next(list_node* next_node);

  list_node* previous() const;
  void previous(list_node* prev_node);

  T data();
  void data(T data);

  list_node& operator=(const list_node& rhs);
  list_node& operator=(const T& rhs);

 private:
  list_node* next_node;
  list_node* prev_node;
  T* node_data;
};



/* Initialize an empty list node and set all pointers to NULL */
template <typename T>
list_node<T>::list_node() {
  node_data = NULL;
  next_node = NULL;
  prev_node = NULL;
}



/* Provides a copy constructor for a list_node */
template <typename T>
list_node<T>::list_node(const list_node& rhs) {
  node_data = rhs.node_data;
  next_node = rhs.next_node;
  prev_node = rhs.prev_node;
}




/* Creates a list_node with node_data set to data */
template <typename T>
list_node<T>::list_node(const T data) {
  this->data(data);
  next_node = NULL;
  prev_node = NULL;
}



/* Destroys this node and the next node. */
template <typename T>
list_node<T>::~list_node() {
  if (next_node != NULL) {
    delete next_node;
  }

  if (node_data != NULL) {
    delete node_data;
  }

  next_node = NULL;
  prev_node = NULL;
  node_data = NULL;
}



/* Returns a reference to the next node */
template <typename T>
list_node<T>* list_node<T>::next() const {
  return next_node;
}



/* Sets the next node's value */
template <typename T>
void list_node<T>::next(list_node<T>* next_node) {
  list_node* temp = this->next_node;

  this->next_node = next_node;

  // disconnect and remove temp
  if (temp != NULL) {
    temp->next_node = NULL;
    delete temp;
  }
}



/* Returns a reference to the previous node. */
template <typename T>
list_node<T>* list_node<T>::previous() const {
  return prev_node;
}



/* Sets the previous node */
template <typename T>
void list_node<T>::previous(list_node<T>* prev_node) {
  if (prev_node == NULL && this->prev_node == NULL) {
    return;
  }

  list_node* temp = this->prev_node;

  this->prev_node = prev_node;

  if (temp) {
    temp->next_node = NULL;
    temp->prev_node = NULL;
    delete temp;
    temp = NULL;
  }
}



/* Returns the data of this node */
template <typename T>
T list_node<T>::data() {
  return *(node_data);
}


/* Sets the node's data */
template <typename T>
void list_node<T>::data(T data) {
  T* new_data = new T(data);
  this->node_data = new_data;
}



template <typename T>
list_node<T>& list_node<T>::operator=(const list_node& rhs) {
  if (this == &rhs) {
    return *this;
  }

  T* temp = node_data;

  node_data = new T(rhs.node_data);

  if (temp != NULL) {
    delete temp;
  }

  this->next_node = rhs.next_node;
  this->prev_node = rhs.prev_node;

  return *this;
}

template <typename T>
list_node<T>& list_node<T>::operator=(const T& rhs) {
  if (*(this->node_data) == rhs) {
    return *this;
  }

  T* temp = node_data;

  node_data = new T(rhs);

  if (temp != NULL) {
    delete temp;
  }

  return *this;
}
#endif
