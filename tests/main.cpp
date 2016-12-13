#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/llstring.h"
#include <iostream>
using namespace std;

/* Here be tests */
TEST_CASE("llstring - Testing equals and append") {
  llstring a("a");

  const char* a_str = new char[a.length()];
  a_str = a.to_cstring();

  cout << "a is '" << a_str << "'" << endl;

  CHECK(a.equals("a"));

  a.append("b");
  const char* ab_str = new char[a.length()];
  ab_str = a.to_cstring();

  cout << "a is now '" << ab_str << "'" << endl;

  CHECK(a.equals("ab"));

  llstring ab;
  ab += "a";
  ab += "b";
  CHECK(ab.equals("ab"));

  ab += a;
  CHECK(ab.equals("abab"));
}
