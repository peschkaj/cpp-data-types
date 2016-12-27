/* Jeremiah Peschka <jpeschka@pdx.edu>

   Implements a doubly linked list
 */

#include "list_node.h"
#include <exception>

#ifndef LIST
#define LIST

template <typename T>
class list {
 public:
  list();
  list(const list& rhs);
  ~list();

  bool push_front(T to_push);
  bool pop_front(T& popped);
  bool insert(T to_add);

  bool push_back(T to_push);
  bool pop_back(T& popped);
  bool append(T to_add);

  list_node<T>* first() const;
  list_node<T>* head() const;
  void head(list_node<T>* rhs);
  void head(T rhs);

  list_node<T>* last() const;
  list_node<T>* tail() const;
  void tail(list_node<T>* rhs);
  void tail(T lhs);

  int count() const;
 private:
  list_node<T>* list_head;
  list_node<T>* list_tail;
  int node_count;
};



/* Default constructor */
template <typename T>
list<T>::list() {
  node_count = 0;
  list_head = list_tail = NULL;
}



/* Copy constructor */
template <typename T>
list<T>::list(const list& rhs) {
  node_count = rhs.node_count;

  list_node<T>* current = rhs.list_head;

  while (current) {
    current = current->next_node;
    this->append(current);
  }
}



/* Destroys the list and all associated data */
template <typename T>
list<T>::~list() {
  if (list_head != NULL) {
    delete list_head;
  }

  list_head = NULL;
  list_tail = NULL;
}



template <typename T>
bool list<T>::push_front(T to_push) {
  list_node<T>* nn = new list_node<T>(to_push);
  list_node<T>* temp;

  if (list_head == NULL) {
    list_head = nn;
    list_tail = nn;
    ++node_count;

    return true;
  }

  temp = list_head;

  nn->next(temp);
  temp->previous(nn);

  list_head = nn;
  ++node_count;

  return true;
}



template <typename T>
bool list<T>::pop_front(T& popped) {
  if (list_head == NULL) {
    return false;
  }

  list_node<T>* temp = list_head;
  popped = temp->data();

  list_head = list_head->next();

  // if (list_head != NULL) {
  //   list_head->previous(NULL);
  // }

  // temp->next(NULL);

  delete temp;
  --node_count;

  return true;
}



template <typename T>
bool list<T>::insert(T to_push) {
  return push_front(to_push);
}



template <typename T>
bool list<T>::push_back(T to_push) {
  list_node<T>* nn = new list_node<T>(to_push);

  if (list_tail == NULL) {
    list_tail = nn;
    list_head = nn;
    ++node_count;

    return true;
  }

  nn->previous(list_tail);
  list_tail->next(nn);
  list_tail = nn;
  ++node_count;

  return true;
}



template <typename T>
bool list<T>::pop_back(T& popped) {
  list_node<T>* temp;
  if (list_tail == NULL) {
    return false;
  }

  popped = list_tail->data();
  --node_count;

  if (list_tail == list_head) {
    delete list_tail;

    list_tail = NULL;
    list_head = NULL;
  } else {
    temp = list_tail;
    list_tail = temp->previous();
    list_tail->next(NULL);
    temp->previous(NULL);

    delete temp;
  }

  return true;
}



template <typename T>
bool list<T>::append(T to_add) {
  return push_back(to_add);
}



template <typename T>
list_node<T>* list<T>::first() const {
  return head();
}



template <typename T>
list_node<T>* list<T>::head() const {
  return list_head;
}



template <typename T>
void list<T>::head(list_node<T>* rhs) {
  list_node<T>* temp = list_head;

  list_head = rhs;
  list_head->next = temp->next();
  list_head->prev = temp->prev();

  if (list_head != NULL) {
    temp->next(NULL);
    temp->prev(NULL);
    delete temp;
  }
}



template <typename T>
void list<T>::head(T rhs) {
  if (list_head == NULL) {
    list_head = new list_node<T>(rhs);
    list_tail = list_head;
    return;
  }

  T* temp = list_head->data;

  list_head->data = new T(rhs);

  if (temp != NULL) {
    delete temp;
  }
}



template <typename T>
list_node<T>* list<T>::last() const {
  return tail();
}



template <typename T>
list_node<T>* list<T>::tail() const {
  return list_tail;
}



template <typename T>
void list<T>::tail(list_node<T>* rhs) {
  if (list_tail == NULL) {
    list_tail = new list_node<T>(rhs);
    list_head = list_tail;

    return;
  }

  list_node<T>* temp = list_tail;

  if (temp->prev()) {
    temp->prev()->next(rhs);
  }

  if (temp != NULL) {
    temp->next(NULL);
    temp->prev(NULL);
    delete temp;
  }
}



template <typename T>
void list<T>::tail(T rhs) {
  if (list_tail == NULL) {
    list_tail = new list_node<T>(rhs);
    list_head = list_tail;

    return;
  }

  T* temp = list_tail->data();
  list_tail->data(rhs);
  delete temp;

  return;
}



template <typename T>
int list<T>::count() const {
  return node_count;
}
#endif
