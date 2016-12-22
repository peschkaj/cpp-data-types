#include "list.h"

#ifndef QUEUE
#define QUEUE

template <typename T>
class queue {
 public:
  queue<T>();
  queue<T>(queue<T>& rhs);
  ~queue<T>();

  bool enqueue(T& item);
  bool dequeue(T& item);
  bool peek(T& item);

  void display();

  bool is_empty();
 private:
  list<T>* q;
};

template <typename T>
queue<T>::queue() {
  // ummmm.... do something?
  q = new list<T>;
}



template <typename T>
queue<T>::~queue() {
  delete q;
}



template <typename T>
bool queue<T>::enqueue(T& item) {
  return q->append(item);
}



template <typename T>
bool queue<T>::dequeue(T& item) {
  bool success = peek(item);

  if (!success) {
    return success;
  }


}



template <typename T>
bool queue<T>::peek(T& item) {
  if (is_empty()) {
    return false;
  }

  item = q->first()->data();

  return true;
}



template <typename T>
bool queue<T>::is_empty() {
  return (q->count() <= 0);
}

#endif
