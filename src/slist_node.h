#include <iostream>

#ifndef SLIST_NODE
#define SLIST_NODE

template <typename T>
class slist_node {
 public:
  slist_node(T data);
  slist_node(const slist_node& rhs);
  ~slist_node();

  slist_node* next();
  void next(slist_node* next_node);

  T data();
  void data(T new_data);

  void display() const;

  slist_node& operator=(const slist_node& rhs);
  slist_node& operator=(const T& rhs);
 private:
  slist_node* next_node;
  T* node_data;
};



template <typename T>
slist_node<T>::slist_node(T data) {
  this->data(data);
  this->next_node = NULL;
}



template <typename T>
slist_node<T>::slist_node(const slist_node& rhs) {
  node_data = new T(rhs.node_data);
  next_node = rhs.next_node;
}



template <typename T>
slist_node<T>::~slist_node() {
  if (node_data) {
    delete node_data;
  }

  if (next_node) {
    delete next_node;
  }

  node_data = NULL;
  next_node = NULL;
}



template <typename T>
slist_node<T>* slist_node<T>::next() {
  return next_node;
}



template <typename T>
void slist_node<T>::next(slist_node<T>* next_node) {
  this->next_node = next_node;
}



template <typename T>
T slist_node<T>::data() {
  return *(node_data);
}



template <typename T>
void slist_node<T>::data(T node_data) {
  T* new_data = new T(node_data);
  this->node_data = new_data;
}



template <typename T>
slist_node<T>& slist_node<T>::operator=(const slist_node& rhs) {
  if (this == rhs) {
    return *this;
  }

  T* temp = node_data;

  node_data = new T(rhs.node_data);
  next_node = rhs.next_node;

  return *this;
}



template <typename T>
slist_node<T>& slist_node<T>::operator=(const T& rhs) {
  if (this->node_data == rhs) {
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
