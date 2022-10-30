#include "queue.h"

#include <stdlib.h>

#include "error.h"

#define INIT_CAPACITY 8
#define GROWTH_FACTOR 2
#define SHRINK_THRESHOLD 0.5

typedef struct Queue {
    // The circular array of the queue.
    void** data;

    // The length of the queue.
    size_t len;

    // The capacity of the queue.
    size_t cap;

    // The front of the queue.
    size_t front;

    // The back of the queue: index of next insertion location.
    size_t back;
} Queue;

Queue* NewQueue() {
    Queue* q = malloc(sizeof(Queue));

    q->data = malloc(sizeof(void*) * INIT_CAPACITY);
    q->len = 0;
    q->cap = INIT_CAPACITY;
    q->front = 0;
    q->back = 0;

    return q;
}

size_t QueueLen(Queue* q) {
    return q->len;
}

// queueUnwind unwinds and copies the contents of the old queue into a resized
// queue buffer.  Note that this function assumes there is enough space for all
// the unwound elements.
void queueUnwind(Queue* q) {
    void** newData = malloc(sizeof(void*) * q->cap);
        
    int j = 0;
    for (int i = q->front; i != q->back; i = (i + 1) % q->cap) {
        newData[j++] = q->data[i];
    }

    free(q->data);
    q->data = newData;

    q->front = 0;
    q->back = q->len;
}


void Enqueue(Queue* q, void* value) {
    if (q->len == q->cap) {
        q->cap *= GROWTH_FACTOR;
        queueUnwind(q);        
    }

    q->data[q->back] = value;

    q->len++;
    q->back = (q->back + 1) % q->cap;
}

void* Dequeue(Queue* q) {
    if (q->len == 0)
        Error("dequeue called on empty queue");

    void* value = q->data[q->front];

    q->front = (q->front + 1) % q->cap;

    if (--q->len > INIT_CAPACITY && q->len < q->cap * SHRINK_THRESHOLD) {
        q->cap *= SHRINK_THRESHOLD;
        queueUnwind(q);
    }

    return value;
}

void* QueueFront(Queue* q) {
    if (q->len > 0)
        return q->data[q->front];

    Error("front called on empty queue");
    return NULL;
}