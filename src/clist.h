/* A list with a tail pointer

   This list is specialized for working with lists of char arrays.
 */

#include "clist_node.h"
typedef clist_node node;

#ifndef CLIST
#define CLIST

class clist {
 public:
  clist();
  ~clist();

  /* Inserts a new item at the tail of the list */
  void insert(const char* data);

  /* Inserts a new item at the head of the list */
  void insert_at_head(const char* data);

  bool empty();

  node* head();
  node* tail();

  operator char* ();
  operator const char* ();

 private:
  int count;
  node* list_head;
  node* list_tail;
};

#endif
