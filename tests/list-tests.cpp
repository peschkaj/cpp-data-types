#include "doctest.h"
#include "../src/list.h"
#include <iostream>

TEST_CASE("list - Creating a list doesn't explode") {
  list<int> l;
  l.push_front(4);

  CHECK(l.head()->data() == 4);
  CHECK(l.tail()->data() == 4);
}

TEST_CASE("list - Tail points to the last element") {
  list<int> l;
  l.append(1);
  l.append(2);
  l.append(3);
  l.append(4);
  l.append(5);
  l.append(6);

  CHECK(l.count() == 6);
  CHECK(l.tail()->data() == 6);
}

TEST_CASE("list = Head points to the first element") {
  list<int> l;
  l.push_back(6);
  l.push_back(5);
  l.push_back(4);
  l.push_back(3);
  l.push_back(2);
  l.push_back(1);

  CHECK(l.count() == 6);
  CHECK(l.head()->data() == 6);
}

TEST_CASE("list - Can append at the end") {
  list<int> l;
  l.push_front(1);
  l.push_back(2);

  CHECK(l.count() == 2);
  CHECK(l.tail()->data() == 2);
}

TEST_CASE("list - Count is correct after insert") {
  list<int> l;

  l.insert(1);
  CHECK(l.count() == 1);

  l.append(2);
  CHECK(l.count() == 2);

  l.push_front(0);
  CHECK(l.count() == 3);

  l.push_back(3);
  CHECK(l.count() == 4);
}

TEST_CASE("list - pop on an empty list does nothing") {
  list<int> l;
  int popped;
  bool success = l.pop_front(popped);

  CHECK(success == false);
}

TEST_CASE("list - Count is correct after remove") {
  list<int> l;

  l.insert(1);
  l.append(2);
  //l.push_front(0);
  //l.push_back(3);
  CHECK(l.count() == 2);

  int popped;

  bool popped_success = l.pop_front(popped);
  CHECK(popped_success == true);
  //CHECK(l.count() == 1);

  // l.pop_back(popped);
  // CHECK(l.count() == 2);
}
