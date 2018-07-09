#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <pthread.h>

#include <gtest/gtest.h>

#define queue_element_t int

#include "queue.h"


TEST(TsQueueTest, QueueCreate) {
  queue_t *q = queue_create(100);
  EXPECT_EQ(0, q->size);
  EXPECT_EQ(100, q->capacity);
  free(q);
}

TEST(TsQueueTest, QueuePushPop) {
  queue_t *q = queue_create(100);
  push(q, 10);
  EXPECT_EQ(1, q->size);
  while (!empty(q)) pop(q);
  EXPECT_EQ(0, q->size);
  free(q);
}

TEST(TsQueueTest, QueuePushPopMI) {
  queue_t *q = queue_create(1000);
  size_t T = 1000;
  int k = 1;

  while (k <= T) {
    push(q, k ++);
  }
  EXPECT_EQ(T, q->size);
  int kk ;
  k = 1;
  while (!empty(q)){
    kk = front(q);
    pop(q);
    EXPECT_EQ(kk, k++);
  }
  EXPECT_EQ(0, size(q));
  free(q);
}

int
main(int argc, char* argv[]){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}