#include "clist.h"
#include <cstring>

clist::clist() {
  list_head = NULL;
  list_tail = list_head;
}

clist::~clist() {
  delete list_head;
  list_head = NULL;
  list_tail = NULL;
}

void clist::insert(const char* data) {
  node* nn = new node(data);

  list_tail->next(nn);
  list_tail = nn;
}
