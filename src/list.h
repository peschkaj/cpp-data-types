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

  list_node<T>* first();
  list_node<T>* head();
  void head(list_node<T>* rhs);
  void head(T rhs);
 private:
  list_node<T> list_head;
  list_node<T> list_tail;
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
  if (list_head) {
    delete list_head;
  }

  list_head = NULL;
  list_tail = NULL;
}



template <typename T>
list_node<T>* list<T>::first() {
  return head();
}



template <typename T>
list_node<T>* list<T>::head() {
  return list_head;
}



template <typename T>
void list<T>::head(list_node<T>* rhs) {
  list_node<T>* temp = list_head;

  list_head = rhs;

  if (list_head != NULL) {
    temp->next(NULL);
    temp->prev(NULL);
    delete temp;
  }
}



template <typename T>
void list<T>::head(T rhs) {
  T* temp = list_head->data;

}
#endif
