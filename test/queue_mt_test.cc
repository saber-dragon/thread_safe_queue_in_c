#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <pthread.h>

#include <gtest/gtest.h>

#define ENABLE_MULTIPLE_THREADS
#define queue_element_t int

#include "queue.h"

#define EACH 100
queue_t *q = nullptr;

void *push_test(void *arg){
  int val = *(int *) arg;
  for (int i=0;i < EACH;++ i )
    push(q, val);
}

void *pop_test(void *arg) {
  for (int i=0;i < EACH;++ i )
  pop(q);
}


TEST(TsQueueTest, QueuePushPop) {
  q = queue_create(1000);
  size_t T = 9;
  int k = 1;


  while (k <= T) {
    pthread_t t;
    pthread_create(&t, NULL, push_test, &k);
    k ++;

    pthread_join(t, NULL);
  }

  EXPECT_EQ(T * EACH, q->size);

  while (!empty(q)){
    pthread_t t;
    pthread_create(&t, NULL, pop_test, NULL);
    pthread_join(t, NULL);
  }

  EXPECT_EQ(0, size(q));
  free(q);
}

int
main(int argc, char* argv[]){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}