#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

// Queue represents a FIFO sequence of elements.
typedef struct Queue Queue;

// NewQueue creates a new queue.
Queue* NewQueue();

// QueueLen returns the length of q.
size_t QueueLen(Queue* q);

// Enqueue adds a value onto the end of q.
void Enqueue(Queue* q, void* value);

// Dequeue pops the value from the front of q and returns it.
void* Dequeue(Queue* q);

// QueueFront returns the element at the front of q if any.
void* QueueFront(Queue* q);

#endif