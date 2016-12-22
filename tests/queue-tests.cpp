#include "../src/queue.h"
#include "doctest.h"

TEST_CASE("queue - an enqueue'd item can be peek'd") {
  queue<int> q;
  int first = 1;
  int peek;

  q.enqueue(first);

  bool success = q.peek(peek);

  CHECK(success == true);
  CHECK(peek == 1);
}
