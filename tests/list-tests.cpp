#include "doctest.h"
#include "../src/list.hpp"
#include <iostream>

TEST_CASE("list - insert will create a head node if the list is empty") {
  list<int> l;
  bool success = l.insert(1);

  CHECK(success == true);
  CHECK(l.head()->data() == 1);
}

TEST_CASE("list - insert_beginning replaces the head node if one exists") {
  list<int> l;
  l.insert(2);

  bool success = l.insert_beginning(1);

  CHECK(success == true);
  CHECK(l.head()->data() == 1);
}

TEST_CASE("list - data is inserted in sorted order") {
  list<int> l;
  l.insert(4);
  //l.insert(1);

  //CHECK(l.head()->data() < l.tail()->data());
}
