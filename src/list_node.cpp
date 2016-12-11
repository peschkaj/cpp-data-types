#include "list_node.h"

list_node::list_node(data_item* data) {
  this->node_data = data;
}



list_node::~list_node() {
  if (node_data) {
    delete node_data;
  }

  delete next_node;
}



list_node* list_node::next() {
  return next_node;
}

void list_node::next(list_node* next_node) {
  this->next_node = next_node;
}



data_item* list_node::data() {
  return node_data;
}

void list_node::data(data_item* node_data) {
  this->node_data = node_data;
}



void list_node::display() const {
  node_data->display();
}
