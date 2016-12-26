#include <iostream>

#ifndef SLIST_NODE
#define SLIST_NODE

template <typename T>
class slist_node {
 public:
  slist_node(T data);
  ~slist_node();

  slist_node* next();
  void next(slist_node* next_node);

  T data();
  void data(T new_data);

  void display() const;

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
#endif
