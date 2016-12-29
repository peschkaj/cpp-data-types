/* Jeremiah Peschka <jpeschka@pdx.edu>

   Implements a doubly linked list
 */

#include "list_node.hpp"
#include <exception>

#ifndef LIST
#define LIST

template <typename T>
class list {
 public:
  list();
  list(const list& rhs);
  ~list();

  bool insert(const T& to_add);
  bool insert_beginning(const T& to_add);
  bool insert_before(list_node<T>*& insert_location, const T& to_add);

  int remove(const T& to_remove);
  int remove_first(const T& to_remove);
  bool remove_one(const T& to_remove);

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
  list_node<T>* insert(list_node<T>* current, const T& to_add);
  int remove(const T& to_remove, list_node<T>* current);
  void remove_one(const T& to_remove, list_node<T>* current, bool& removed);
  list_node<T>* list_head;
  list_node<T>* list_tail;
  int node_count;
};



/* Default constructor */
template <typename T>
list<T>::list() {
  node_count = 0;
  list_head = NULL;
  list_tail = NULL;
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
  list_node<T>* current;

  while (list_head) {
    current = list_head;
    list_head = list_head->next();
    delete current;
  }

  list_head = NULL;
  list_tail = NULL;
  node_count = 0;
}



template <typename T>
bool list<T>::insert(const T& to_add) {
  if (list_head == NULL) {
    return insert_beginning(to_add);
  }

  list_head = insert(list_head, to_add);

  return false;
}



template <typename T>
list_node<T>* list<T>::insert(list_node<T>* current, const T& to_add) {
  list_node<T>* new_node;

  if (to_add < current->data()) {
    current = insert(current->next(), to_add);
  } else {
    new_node = new list_node<T>(to_add);
    new_node->next(current->next());

    new_node->previous(current->previous());
    current->previous()->next(new_node);
    current->previous(new_node);

    current = new_node;
  }

  return current;
}



template <typename T>
bool list<T>::insert_beginning(const T& to_add) {
  bool success = false;
  list_node<T>* new_node = new list_node<T>(to_add);

  if (list_head == NULL) {
    list_head = new_node;
    list_tail = new_node;
    success = true;
  } else if (list_head->data() == to_add) {
    success = false;
  } else {
    list_head->previous(new_node);
    new_node->next(list_head);
    list_head = new_node;
    success = true;
  }

  return success;
}



template <typename T>
int list<T>::remove(const T& to_remove) {
  if (list_head == NULL) {
    return 0;
  }

  return remove(to_remove, list_head);
}



template <typename T>
int list<T>::remove(const T& to_remove, list_node<T>* current) {
  int deleted = 0;

  if (current == NULL) {
    return deleted;
  }

  deleted += remove(to_remove, current->next());

  if (current->data() == current) {
    current->next(current->previous()->next());
    current->next->previous(current->previous());

    delete current;

    ++deleted;
    --node_count;
  }

  return deleted;
}



template <typename T>
int list<T>::remove_first(const T& to_remove) {
  return 0;
}



template <typename T>
bool list<T>::remove_one(const T& to_remove) {
  bool deleted = false;
  if (list_head == NULL) {
    return deleted;
  }

  remove_one(to_remove, list_head, deleted);

  return deleted;
}



template <typename T>
void list<T>::remove_one(const T &to_remove, list_node<T>* current, bool& deleted) {
  list_node<T>* temp;

  if (current == NULL || deleted == true) {
    return;
  }

  if (current->data() == to_remove) {
    temp = current;

    if (current == list_head) {
      list_head = current->next();
    }

    if (current == list_tail) {
      list_tail = current->previous();
    }





    deleted = true;
    --node_count;
  }
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
