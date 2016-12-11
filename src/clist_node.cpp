#include "clist_node.h"
#include <cstring>

clist_node::clist_node() {
  node_data = NULL;
  next_node = NULL;
  data_length = 0;
}

clist_node::clist_node(char* data) {
  node_data = new char[strlen(data) + 1];
  strcpy(node_data, data);

  data_length = strlen(data);
  next_node = NULL;
}

clist_node::clist_node(const char* data) {
  node_data = new char[strlen(data) + 1];
  strcpy(node_data, data);

  data_length = strlen(data);
  next_node = NULL;
}



clist_node::~clist_node() {
  if (node_data) {
    delete node_data;
  }

  delete next_node;
}



clist_node* clist_node::next() {
  return next_node;
}



void clist_node::next(clist_node* next_node) {
  this->next_node = next_node;
}



char* clist_node::data() {
  return node_data;
}



void clist_node::data(char* node_data) {
  this->node_data = node_data;
  data_length = strlen(node_data);
}



int clist_node::length() {
  return data_length;
}
