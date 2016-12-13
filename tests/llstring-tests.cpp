#include "doctest.h"
#include "../src/llstring.h"


/* Here be tests */
TEST_CASE("Testing the char* conversion") {
  clist a;
  a += "a";

  CHECK((char*)a == "a");
}
