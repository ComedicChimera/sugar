#include "vec.h"

#include <stdlib.h>

#include "error.h"

#define INIT_CAPACITY 8
#define GROWTH_FACTOR 2
#define SHRINK_THRESHOLD 0.5

typedef struct Vec {
    // The vector's internal data buffer.
    void** data;

    // The length of the vector.
    size_t len;

    // The capacity of the vector.
    size_t cap;
} Vec;

Vec* NewVec() {
    Vec* vec = malloc(sizeof(Vec));

    vec->data = malloc(sizeof(void*) * INIT_CAPACITY);
    vec->len = 0;
    vec->cap = INIT_CAPACITY;

    return vec;
}

size_t VecLen(Vec* vec) {
    return vec->len;
}

void* VecGet(Vec* vec, size_t ndx) {
    if (ndx < vec->len)
        return vec->data[ndx];

    Error("vector index %d out of bounds", ndx);
    return NULL;
}

void VecSet(Vec* vec, size_t ndx, void* value) {
    if (ndx < vec->len)
        vec->data[ndx] = value;

    Error("vector index %d out of bounds", ndx);
}

void VecPush(Vec* vec, void* value) {
    if (vec->len == vec->cap) {
        vec->cap *= GROWTH_FACTOR;
        vec->data = realloc(vec->data, vec->cap);
    }

    vec->data[vec->len++] = value;
}

void* VecPop(Vec* vec) {
    if (vec->len == 0)
        Error("pop called on empty vector");

    void* value = vec->data[--vec->len];

    if (vec->len > INIT_CAPACITY && vec-> len < vec->cap * SHRINK_THRESHOLD) {
        vec->cap *= SHRINK_THRESHOLD;
        vec->data = realloc(vec->data, vec->cap);
    }

    return value;
}
