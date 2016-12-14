#include "clist.h"
#include <cstring>

clist::clist() {
  list_head = NULL;
  list_tail = list_head;
  count = 0;
  size = 0;
}

clist::clist(const clist& rhs) {
  node* current;

  list_head = list_tail = NULL;

  current = rhs.list_head;

  while (current) {
    insert(current->data());

    current = current->next();
  }
}

clist::~clist() {
  delete list_head;
  list_head = NULL;
  list_tail = NULL;
}

void clist::insert(const char* data) {
  node* nn = new node(data);

  if (!list_tail) {
    list_head = nn;
    list_tail = nn;
  } else {
    list_tail->next(nn);
    list_tail = nn;
  }

  ++count;
  size += strlen(data);
}



void clist::insert_at_head(const char* data) {
  node* nn = new node(data);

  insert_at_head(nn);

  ++count;
  size += strlen(data);
}

void clist::insert_at_head(node*& to_add) {
  to_add->next(list_head);
  list_head = to_add;
}



bool clist::empty() const {
  return (count == 0);
}

int clist::length() const {
  return size;
}



node* clist::head() {
  return list_head;
}

node* clist::tail() {
  return list_tail;
}



/* Converts our list of char* into a single char* */
// clist::operator char* () {
//   node* current;
//   char* buffer;

//   if (size == 0) {
//     return NULL;
//   }

//   buffer = new char[size + 1];
//   current = list_head;

//   while (current) {
//     strcat(buffer, current->data());

//     current = current->next();
//   }

//   buffer[size] = '\0';

//   return buffer;
// }




// /* Converts our list of char* into a const char* */
// clist::operator const char *() {
//   return (const char*)((char *)this);
// }



/* Append characters to this list */
int clist::append(const char* rhs) {
  int appended = 0;

  insert(rhs);
  appended = strlen(rhs);

  return appended;
}



/* Append another clist to this one */
clist& clist::operator+=(const clist& rhs) {
  node* current;
  char* buffer;
  int len;

  if (count == 0) {
    return *this;
  }

  current = rhs.list_head;

  while (current) {
    len = current->length();

    buffer = new char[len + 1];
    strcpy(buffer, current->data());
    insert(buffer);
    delete[] buffer;

    current = current->next();
    size += len;
  }

  return *this;
}

clist& clist::operator+=(const char* rhs) {
  insert(rhs);
  size += strlen(rhs);
  return *this;
}

clist& clist::operator+=(char* rhs) {
  insert(rhs);
  size += strlen(rhs);
  return *this;
}

char* clist::to_cstring() {
  node* current = NULL;
  char* buffer = NULL;

  if (size == 0) {
    return NULL;
  }

  buffer = new char[size + 1]();
  current = list_head;

  while (current) {
    strcat(buffer, current->data());

    current = current->next();
  }

  buffer[size] = '\0';

  return buffer;
}
