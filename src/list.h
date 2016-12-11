#include "list_node.h"

typedef list_node node;

#ifndef LIST
#define LIST

class list {
 public:
  list();
  ~list();

  node* head();
  void head(node* new_head);

  int count() const;
  int display() const;

  bool insert(data_item* to_add);
  bool remove(data_item* to_remove);
 private:
  node* list_head;
  int node_count;

  node* remove(node* current, data_item* to_remove, bool& success);
  void display(list_node* current) const;
};

#endif
