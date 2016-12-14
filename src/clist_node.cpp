#include "clist_node.h"
#include <cstring>

clist_node::clist_node() {
  node_data = NULL;
  next_node = NULL;
  data_length = 0;
}

clist_node::clist_node(char* data) {
  int len = strlen(data) + 1;
  node_data = new char[len];
  strcpy(node_data, data);

  data_length = len;
  next_node = NULL;
}

clist_node::clist_node(const char* data) {
  int len = strlen(data) + 1;
  node_data = new char[len];
  strcpy(node_data, data);

  data_length = len;
  next_node = NULL;
}



clist_node::~clist_node() {
  if (node_data) {
    delete[] node_data;
  }

  if (next_node) {
    delete next_node;
  }

  node_data = NULL;
  next_node = NULL;
}



clist_node* clist_node::next() {
  if (!next_node) {
    return NULL;
  }

  return next_node;
}



void clist_node::next(clist_node*& next_node) {
  this->next_node = next_node;
}



const char* clist_node::data() const {
  return node_data;
}



void clist_node::data(char* node_data) {
  int len = strlen(node_data) + 1;

  this->node_data = new char[len];
  strcpy(this->node_data, node_data);

  data_length = len;
}



int clist_node::length() {
  return data_length;
}
