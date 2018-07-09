/**
  * Simple thread-safe FIFO queue.
  * 
  * This file simply adds a thread-safe wrapper to 
  * the data structure provided at 
  * https://github.com/junjizhi/fifo
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#ifdef ENABLE_MULTIPLE_THREADS
#include <pthread.h>
pthread_mutex_t _local_mutex_q = PTHREAD_MUTEX_INITIALIZER;
#endif // ENABLE_MULTIPLE_THREADS

/* Create a queue */
queue_t *
queue_create(size_t cap) {
  assert ( cap > 0 && "Cap should be at least 1");

  queue_t *q = (queue_t *) malloc( sizeof(queue_t) );
  q->size = 0;
  q->capacity = cap;

  INIT_LIST_HEAD(&q->list);

  return q;

}

/* queue pop() */
void 
pop(queue_t *q) {
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_lock(&_local_mutex_q);
  #endif
    if (q->size == 0) {
      fprintf(stderr, "%s: queue is empty", __FUNCTION__);
      return;
    }
    -- q->size;
    queue_t *tmp = list_entry(q->list.next, queue_t, list);
    list_del(q->list.next);
    free (tmp);
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_unlock(&_local_mutex_q);
  #endif
}

queue_element_t 
front(queue_t *q) {
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_lock(&_local_mutex_q);
  #endif 

  assert( q->size > 0 && "Queue is empty" );

  struct list_head *first = q->list.next;
  queue_t *first_element = list_entry(first, queue_t, list);
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_unlock(&_local_mutex_q);
  #endif 

  return first_element->data;
}

void 
push(queue_t *q, queue_element_t element){
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_lock(&_local_mutex_q);
  #endif
    if ( q->size == q->capacity ) {
      fprintf(stderr, "%s: queue is full.\n", __FUNCTION__);
      return;
    }
    ++ q->size;
    queue_t *new_node = (queue_t *) malloc(sizeof(queue_t));
    new_node->data = element;
    list_add_tail(&(new_node->list), &(q->list));
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_unlock(&_local_mutex_q);
  #endif     
}

int 
empty(queue_t *q){
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_lock(&_local_mutex_q);
  #endif
    return (q->size == 0);
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_unlock(&_local_mutex_q);
  #endif
}

size_t
size(queue_t *q){
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_lock(&_local_mutex_q);
  #endif
    return q->size;
  #ifdef ENABLE_MULTIPLE_THREADS
    pthread_mutex_unlock(&_local_mutex_q);
  #endif  
}


size_t 
capacity(queue_t *q){
  return q->capacity;
}