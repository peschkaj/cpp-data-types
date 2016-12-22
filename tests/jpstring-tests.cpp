#include "doctest.h"
#include "../src/jpstring.h"
#include <iostream>

using namespace std;

TEST_CASE("jpstring - basic equality") {
  jpstring a("a");

  CHECK(a == "a");
}

TEST_CASE("jpstring - adding produces equal strings") {
  jpstring a("a");
  a += "b";

  CHECK(a == "ab");
}

TEST_CASE("jpstring - splitting produces an array of strings") {
  jpstring a("this is a really long string");
  list<jpstring>* parts = a.split();

  CHECK(parts->head()->data() == "this");
  CHECK(parts->tail()->data() == "string");

  delete parts;
}

TEST_CASE("jpstring - assignment tests") {
  jpstring a("this is a really long string");

  const char* b = "this is an even longer string!";

  a = b;
  CHECK(a == b);
}
