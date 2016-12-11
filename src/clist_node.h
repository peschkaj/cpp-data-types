/* A list node.

   This list node is specialized for working with char arrays.

   TODO: Implement stream operators
 */

#ifndef CLIST_NODE
#define CLIST_NODE

class clist_node {
 public:
  clist_node();
  clist_node(char* data);
  clist_node(const char* data);
  ~clist_node();

  clist_node* next();
  void next(clist_node* next_node);

  char* data();
  void data(char* new_data);

  int length();
 private:
  clist_node* next_node;
  char* node_data;
  int data_length;
};

#endif
