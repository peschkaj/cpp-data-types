#include "doctest.h"
#include "../src/list.h"

TEST_CASE("Creating a list doesn't explode") {
  list<int> l;
  l.insert(4);

  CHECK(l.head()->data() == 4);
}
