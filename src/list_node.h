#ifndef LIST_NODE
#define LIST_NODE

template <typename T>
class list_node {
 public:
  list_node(T data);
  ~list_node();

  list_node* next();
  void next(list_node* next_node);

  T data();
  void data(T new_data);

  void display() const;

 private:
  list_node* next_node;
  T* node_data;
};



template <typename T>
list_node<T>::list_node(T data) {
  this->data(data);
}



template <typename T>
list_node<T>::~list_node() {
  if (node_data) {
    delete node_data;
  }

  delete next_node;
}



template <typename T>
list_node<T>* list_node<T>::next() {
  return next_node;
}



template <typename T>
void list_node<T>::next(list_node<T>* next_node) {
  this->next_node = next_node;
}



template <typename T>
T list_node<T>::data() {
  return *(node_data);
}



template <typename T>
void list_node<T>::data(T node_data) {
  T* new_data = new T(node_data);
  this->node_data = new_data;
}



// FIXME replace with <<
// TODO implement (char *) conversion
template <typename T>
void list_node<T>::display() const {
  node_data->display();
}



#endif
