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
  clist(const clist& rhs);
  ~clist();

  /* Inserts a new item at the tail of the list */
  void insert(const char* data);

  /* Inserts a new item at the head of the list */
  void insert_at_head(const char* data);

  bool empty() const;
  int length() const;

  node* head();
  node* tail();

  /* Conversion operators */
  // operator char* ();
  // operator const char* ();
  char* to_cstring();

  /* Append a thing */
  int append(const char* rhs);
  clist& operator+=(const clist& rhs);
  clist& operator+=(const char* rhs);
  clist& operator+=(char* rhs);

 private:
  void insert_at_head(node*& to_add);
  int count;
  int size;
  node* list_head;
  node* list_tail;
};

#endif
