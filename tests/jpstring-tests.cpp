#include "doctest.h"
#include "../src/jpstring.h"
#include <iostream>

using namespace std;

TEST_CASE("jpstring - basic equality") {
  jpstring a("a");

  CHECK(a == "a");
}
