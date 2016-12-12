#include "list.h"
#include <cstdlib>

list::list() {
  list_head = NULL;
  node_count = 0;
}

list::~list() {
  delete list_head;
  list_head = NULL;
}




node* list::head() {
  return list_head;
}

void list::head(node* new_head) {
  node* tmp = list_head;

  list_head = new_head;

  if (tmp != NULL) {
    list_head->next(tmp->next());

    tmp->next(NULL);
    delete tmp;
  }
}



int list::count() const {
  return node_count;
}



int list::display() const {
  display(list_head);

  return node_count;
}

void list::display(list_node* current) const {
  if (current == NULL) {
    return;
  }

  current->display();

  display(current->next());
}



bool list::insert(data_item* to_add) {
  node* new_node = new node(to_add);
  new_node->next(list_head);
  list_head = new_node;

  return true;
}



bool list::remove(data_item* to_remove) {
  bool success = false;

  list_head = remove(list_head, to_remove, success);

  return success;
}

node* list::remove(node* current, data_item* to_remove, bool& success) {
  if (current == NULL) {
    return NULL;
  }

  current->next(remove(current->next(),
                       to_remove,
                       success));

  if (current->data() == to_remove) {
    node* temp = current;
    current = current->next();

    temp->next(NULL);
    delete temp;

    success = true;
  }

  return current;
}
