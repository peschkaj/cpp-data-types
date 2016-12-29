#include "../src/stack.hpp"
#include "doctest.h"

TEST_CASE("stack - the first item in the stack can be peeked") {
  stack<int> s;
  int first = 1;
  int peek;

  s.push(first);

  bool success = s.peek(peek);

  CHECK(success == true);
  CHECK(peek == 1);
}

TEST_CASE("stack - The last item in the stack is the first item popped") {
  stack<int> s;
  int one, two, popped;
  one = 1;
  two = 2;

  s.push(two);
  s.push(one);

  bool success = s.pop(popped);

  CHECK(success == true);
  CHECK(popped == one);
}

TEST_CASE("stack - popping an empty stack returns false") {
  stack<int> s;
  int popped;

  bool success = s.pop(popped);

  CHECK(success == false);
}
