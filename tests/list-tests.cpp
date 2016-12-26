#include "doctest.h"
#include "../src/list.h"

TEST_CASE("list - Creating a list doesn't explode") {
  list<int> l;
  l.insert(4);

  CHECK(l.head()->data() == 4);
  CHECK(l.tail()->data() == 4);
}

TEST_CASE("list - Tail points to the last element") {
  list<int> l;
  l.insert(4);
  l.insert(5);
  l.insert(6);
  CHECK(l.head()->data() == 6);
  CHECK(l.tail()->data() == 4);

  bool removed = l.remove(4);


  if (removed) {
    CHECK(l.tail()->data() != 4);
  }
}

TEST_CASE("list - Can append at the end") {
  list<int> l;
  l.insert(4);
  l.insert(3);

  l.append(5);

  CHECK(l.tail()->data() == 5);
}

TEST_CASE("list - Insert adds at the beginning") {
  list<int> l;
  l.insert(1);

  CHECK(l.head()->data() == 1);

  l.insert(2);
  CHECK(l.head()->data() == 2);
}

TEST_CASE("list - count is correct after inserts") {
  list<int> l;

  l.insert(1);
  CHECK(l.count() == 1);

  l.insert(2);
  CHECK(l.count() == 2);

  l.insert(3);
  CHECK(l.count() == 3);
}

TEST_CASE("list - count is correct after append") {
  list<int> l;

  l.insert(1);
  l.insert(2);
  l.insert(3);

  l.append(4);
  CHECK(l.count() == 4);
}

TEST_CASE("list - count is correct after removal") {
  list<int> l;
  int count;

  l.insert(1);
  l.insert(2);
  l.insert(3);

  count = l.count();

  l.remove(1);

  CHECK(l.count() == (count - 1));
}

TEST_CASE("list - removing from an empty list returns false") {
  list<int> l;
  bool success;

  success = l.remove(9);

  CHECK(success == false);
}

TEST_CASE("list - removing an item that doesn't exist returns false") {
  list<int> l;
  bool success;
  l.insert(1);

  success = l.remove(9);

  CHECK(success == false);
}

TEST_CASE("list - remove_one only removes one node") {
  list<int> l;

  l.insert(1);
  l.insert(2);
  l.insert(1);

  bool success = l.remove_one(1);

  CHECK(success == true);
  CHECK(l.head()->data() == 2);
  CHECK(l.tail()->data() == 1);
}

TEST_CASE("list - remove_one on an empty list does nothing") {
  list<int> l;

  bool success = l.remove_one(0);

  CHECK(success == false);
}

TEST_CASE("list - emptying a list with remove_one resets tail pointer correctly") {
  list<int> l;

  l.insert(1);

  bool success = l.remove_one(1);

  CHECK(success == true);

  if (l.tail() == NULL) {
    CHECK(1 == 1);
  } else {
    CHECK(1 == 2);
  }
}

TEST_CASE("list - a list can be converted to an array") {
  list<int> l;
  l.insert(0);
  l.append(1);
  l.append(2);
  l.append(3);

  int* arr;
  int count = l.to_array(arr);

  CHECK(count == 4);
  CHECK(arr[0] == 0);
  CHECK(arr[1] == 1);
  CHECK(arr[2] == 2);
  CHECK(arr[3] == 3);

}
