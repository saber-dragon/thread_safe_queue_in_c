#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include "list.h"


#ifndef queue_element_t
#define queue_element_t void*
#endif

typedef struct {
    size_t capacity;
    size_t size;
    queue_element_t data;
    struct list_head list;
} queue_t;

#ifdef __cplusplus
extern "C" {
#endif
queue_t *queue_create(size_t cap);
queue_element_t front(queue_t *q);
void push(queue_t *q, queue_element_t new_element);
void pop(queue_t *q);
int empty(queue_t *q);
size_t size(queue_t *q);
size_t capacity(queue_t *q);

#ifdef __cplusplus
}
#endif

#endif // THREAD_SAFE_QUEUE_H