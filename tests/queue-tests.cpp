#include "../src/queue.hpp"
#include "doctest.h"

TEST_CASE("queue - enqueue on an empty queue returns true") {
  queue<int> q;
  int one = 1;

  bool success = q.enqueue(one);

  CHECK(success == true);
}

TEST_CASE("queue - the top value can be peeked") {
  queue<int> q;
  int one = 1;
  int two = 2;
  int three = 3;
  int peeked;

  q.enqueue(one);
  q.enqueue(two);
  q.enqueue(three);

  bool success = q.peek(peeked);

  CHECK(success == true);
  CHECK(peeked == three);
}

TEST_CASE("queue - dequeue on an empty queue returns false") {
  queue<int> q;
  int removed;
  bool success;

  success = q.dequeue(removed);

  CHECK(success == false);
}

TEST_CASE("queue - dequeue on a populated queue dequeues the first item") {
  queue<int> q;
  int one = 1;
  int two = 2;
  int three = 3;
  int removed;

  q.enqueue(one);
  q.enqueue(two);
  q.enqueue(three);

  bool success = q.dequeue(removed);

  CHECK(success == true);
  CHECK(removed == 3);
}
