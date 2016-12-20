#include "doctest.h"
#include "../src/list.h"

TEST_CASE("list - Creating a list doesn't explode") {
  list<int> l;
  l.insert(4);

  CHECK(l.head()->data() == 4);
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
