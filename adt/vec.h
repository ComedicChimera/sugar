#ifndef _VEC_H_
#define _VEC_H_

#include <stdint.h>

// Vec represents a resizeable collection of elements.
typedef struct Vec Vec;

// NewVec creates a new vector.
Vec* NewVec();

// VecLen returns the length of vec.
size_t VecLen(Vec* vec);

// VecGet returns the element at ndx in vec.
void* VecGet(Vec* vec, size_t ndx);

// VecSet sets the element at ndx in vec to value.
void VecSet(Vec* vec, size_t ndx, void* value);

// VecPush pushes a value onto the end of vec.
void VecPush(Vec* vec, void* value);

// VecPop pops an element of the end of vec and returns it.
void* VecPop(Vec* vec);

#endif