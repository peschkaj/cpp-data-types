#include "doctest.h"
#include "../src/stringbuilder.h"
#include <iostream>
using namespace std;

/* Here be tests */

TEST_CASE("stringbuilder - Testing equals and append") {
  stringbuilder a("a");
  CHECK(a.equals("a"));

  a.append("b");
  CHECK(a.equals("ab"));

}

TEST_CASE("stringbuilder - operator+=") {
  stringbuilder ab;
  ab += "a";
  ab += "b";
  CHECK(ab.equals("ab"));

  ab += ab;
  CHECK(ab.equals("abab"));
}

TEST_CASE("stringbuilder - operator+") {
  stringbuilder op_a("a");
  stringbuilder op_b("b");
  stringbuilder op_ab = op_a + op_b;

  CHECK(op_ab.equals("ab"));
}

TEST_CASE("stringbuilder - operator==") {
  stringbuilder a("a");
  CHECK(a == "a");

  a += "b";
  CHECK(a == "ab");
}

TEST_CASE("stringbuilder - can pretend to be a char*") {
  stringbuilder a("a");
  CHECK(strcmp((char *)a, "a") == 0);
  CHECK(strcmp((const char*)a, "a") == 0);
  CHECK(strcmp(a, "a") == 0);
}

TEST_CASE("stringbuilder - copy constructor produces a valid copy") {
  stringbuilder a("a");
  stringbuilder b = a;

  CHECK(b == "a");
  CHECK(a == b);
}

TEST_CASE("stringbuilder - operator== tests") {
  stringbuilder a("a");
  stringbuilder b("a");

  CHECK(a == b);
}
