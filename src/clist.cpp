#include "clist.h"
#include <cstring>

clist::clist() {
  list_head = NULL;
  list_tail =  list_head;
  count = 0;
  size = 0;
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

  ++count;
  size += strlen(data);
}

void clist::insert_at_head(const char* data) {
  node* nn = new node(data);
  nn->next(list_head);
  list_head = nn;

  ++count;
  size += strlen(data);
}

bool clist::empty() const {
  return !(count == 0);
}

node* clist::head() {
  return list_head;
}

node* clist::tail() {
  return list_tail;
}

clist::operator char* () {
  node* current;
  char* buffer, * data_buffer;

  if (size == 0) {
    return NULL;
  }

  buffer = new char[size + 1];
  current = list_head;

  while (current) {
    strcat(buffer, current->data());

    current = current->next();
  }

  return buffer;
}
