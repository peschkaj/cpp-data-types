#include "doctest.h"
#include "../src/llstring.h"
#include <iostream>
using namespace std;

TEST_CASE("llstring - Testing equals and append") {
  llstring a("a");
  CHECK(a.equals("a"));

  a.append("b");
  CHECK(a.equals("ab"));

}

TEST_CASE("llstring - operator+=") {
  llstring ab;
  ab += "a";
  ab += "b";
  CHECK(ab.equals("ab"));

  ab += ab;
  CHECK(ab.equals("abab"));
}

TEST_CASE("llstring - operator+") {
  llstring op_a("a");
  llstring op_b("b");
  llstring op_ab = op_a + op_b;

  CHECK(op_ab.equals("ab"));
}
