#include "doctest.h"
#include "../src/slist.h"

TEST_CASE("slist - Creating an slist doesn't explode") {
  slist<int> l;
  l.insert(4);

  CHECK(l.head()->data() == 4);
  CHECK(l.tail()->data() == 4);
}

TEST_CASE("slist - Tail points to the last element") {
  slist<int> l;
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

TEST_CASE("slist - Can append at the end") {
  slist<int> l;
  l.insert(4);
  l.insert(3);

  l.append(5);

  CHECK(l.tail()->data() == 5);
}

TEST_CASE("slist - Insert adds at the beginning") {
  slist<int> l;
  l.insert(1);

  CHECK(l.head()->data() == 1);

  l.insert(2);
  CHECK(l.head()->data() == 2);
}

TEST_CASE("slist - count is correct after inserts") {
  slist<int> l;

  l.insert(1);
  CHECK(l.count() == 1);

  l.insert(2);
  CHECK(l.count() == 2);

  l.insert(3);
  CHECK(l.count() == 3);
}

TEST_CASE("slist - count is correct after append") {
  slist<int> l;

  l.insert(1);
  l.insert(2);
  l.insert(3);

  l.append(4);
  CHECK(l.count() == 4);
}

TEST_CASE("slist - count is correct after removal") {
  slist<int> l;
  int count;

  l.insert(1);
  l.insert(2);
  l.insert(3);

  count = l.count();

  l.remove(1);

  CHECK(l.count() == (count - 1));
}

TEST_CASE("slist - removing from an empty list returns false") {
  slist<int> l;
  bool success;

  success = l.remove(9);

  CHECK(success == false);
}

TEST_CASE("slist - removing an item that doesn't exist returns false") {
  slist<int> l;
  bool success;
  l.insert(1);

  success = l.remove(9);

  CHECK(success == false);
}

TEST_CASE("slist - remove_one only removes one node") {
  slist<int> l;

  l.insert(1);
  l.insert(2);
  l.insert(1);

  bool success = l.remove_one(1);

  CHECK(success == true);
  CHECK(l.head()->data() == 2);
  CHECK(l.tail()->data() == 1);
}

TEST_CASE("slist - remove_one on an empty list does nothing") {
  slist<int> l;

  bool success = l.remove_one(0);

  CHECK(success == false);
}

TEST_CASE("slist - emptying a list with remove_one resets tail pointer correctly") {
  slist<int> l;

  l.insert(1);

  bool success = l.remove_one(1);

  CHECK(success == true);

  if (l.tail() == NULL) {
    CHECK(1 == 1);
  } else {
    CHECK(1 == 2);
  }
}

TEST_CASE("slist - a list can be converted to an array") {
  slist<int> l;
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

  delete[] arr;
}
