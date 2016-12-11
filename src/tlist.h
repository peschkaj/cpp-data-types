/* A list with a tail pointer */
#include "list_node.h"
typedef list_node node;

#ifndef TLIST
#define TLIST

class tlist {
 public:
  tlist();
  ~tlist();

  /* Inserts a new item at the tail of the list */
  void insert(data_item data);

  /* Inserts a new item at the head of the list */
  void insert_at_head(data_item data);

  bool empty();

  node* head();
  node* tail();

 private:
  int count;
  node* list_head;
  node* list_tail;
};

#endif
