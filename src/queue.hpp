#include "slist_node.h"

#ifndef QUEUE
#define QUEUE

template <typename T>
class queue {
 public:
  queue();
  ~queue();

  bool enqueue(T& item);
  bool dequeue(T& item);

  bool peek(T& item);

  bool is_empty();

 private:
  slist_node<T>* qptr;
};

template <typename T>
queue<T>::queue() {
  qptr = NULL;
}

template <typename T>
queue<T>::~queue() {
  slist_node<T>* current, * temp;

  if (qptr == NULL) {
    return;
  }

  current = qptr->next();
  qptr->next(NULL);

  do {
    temp = current;
    current = current->next();
    temp->next(NULL);
    delete temp;
  } while (current != NULL);
}

template <typename T>
bool queue<T>::enqueue(T& item) {
  bool success = false;
  slist_node<T>* new_node, * temp;
  new_node = new slist_node<T>(item);

  if (qptr == NULL) {
    // queue is empty
    qptr = new_node;
    new_node->next(qptr);

    success = true;
  } else {
    // add at the end
    temp = qptr->next();
    qptr->next(new_node);
    qptr = qptr->next();
    new_node->next(temp);

    success = true;
  }

  return success;
}



template <typename T>
bool queue<T>::dequeue(T& item) {
  if (qptr == NULL) {
    return false;
  }

  item = qptr->data();

  if (qptr == qptr->next()) {
    qptr->next(NULL);
    delete qptr;
    qptr = NULL;
  } else {
    slist_node<T>* next = qptr->next();
    slist_node<T>* temp = next->next();

    qptr->next(next);

    temp->next(NULL);
    delete temp;
  }

  return true;
}

template <typename T>
bool queue<T>::peek(T& item) {
  if (qptr == NULL) {
    return false;
  }

  item = qptr->data();

  return true;
}

#endif
