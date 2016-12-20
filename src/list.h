#include "list_node.h"
#include <cstdlib>

#ifndef LIST
#define LIST

template<typename T>
class list {
 public:
  list();
  ~list();

  list_node<T>* head();
  void head(list_node<T>* new_head);

  list_node<T>* tail();

  int count() const;
  int display() const;

  bool insert(T to_add);
  bool append(T to_add);
  bool remove(const T& to_remove);
 private:
  list_node<T>* list_head;
  list_node<T>* list_tail;
  int node_count;

  list_node<T>* remove(list_node<T>* current, const T& to_remove, bool& success);
  void display(list_node<T>* current) const;
};



template <typename T>
list<T>::list() {
  list_head = NULL;
  list_tail = NULL;
  node_count = 0;
}



template <typename T>
list<T>::~list() {
  delete list_head;
  list_head = NULL;
  list_tail = NULL;
}



template <typename T>
list_node<T>* list<T>::head() {
  return list_head;
}



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

template <typename T>
list_node<T>* list<T>::tail() {
  return list_tail;
}



template <typename T>
int list<T>::count() const {
  return node_count;
}



template <typename T>
int list<T>::display() const {
  display(list_head);

  return node_count;
}



template <typename T>
void list<T>::display(list_node<T>* current) const {
  if (current == NULL) {
    return;
  }

  current->display();

  display(current->next());
}



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

  return true;
}



template <typename T>
bool list<T>::remove(const T& to_remove) {
  bool success = false;

  list_head = remove(list_head, to_remove, success);

  return success;
}



template <typename T>
list_node<T>* list<T>::remove(list_node<T>* current,
                              const T& to_remove,
                              bool& success) {
  if (current == NULL) {
    return NULL;
  }

  current->next(remove(current->next(),
                       to_remove,
                       success));

  if (list_tail != current && current->next() == NULL) {
    list_tail = current;
  }

  if (current->data() == to_remove) {
    list_node<T>* temp = current;
    current = current->next();

    temp->next(NULL);
    delete temp;
    temp = NULL;

    --node_count;

    success = true;
  }

  return current;
}
#endif
