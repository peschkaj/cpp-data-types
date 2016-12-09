#include "list_node.h"

typedef list_node node;

#ifndef LIST
#define LIST

class list {
 public:
  list();
  ~list();
 private:
  node* head;
  int count;
};

#endif
