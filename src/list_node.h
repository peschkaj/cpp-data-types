// FIXME Replace `int` with your own data type when you use this.
class dummy_type {
 public:
  void display();
};

typedef dummy_type data_item;

#ifndef LIST_NODE
#define LIST_NODE

class list_node {
 public:
  list_node(data_item* data);
  ~list_node();

  list_node* next();
  void next(list_node* next_node);

  data_item* data();
  void data(data_item* new_data);

  void display() const;

 private:
  list_node* next_node;
  data_item* node_data;
};

#endif
