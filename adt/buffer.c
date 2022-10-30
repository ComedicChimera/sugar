#include "buffer.h"

#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 8
#define GROWTH_FACTOR 2

typedef struct Buffer {
    char* data;
    size_t len;
    size_t cap;
} Buffer;

Buffer* NewBuffer() {
    Buffer* buff = malloc(sizeof(Buffer));
    
    buff->data = malloc(INIT_CAPACITY * sizeof(char));
    buff->len = 0;
    buff->cap = INIT_CAPACITY;

    return buff;
}

void BufferWriteChar(Buffer* buff, char c) {
    if (buff->len == buff->cap) {
        buff->cap *= GROWTH_FACTOR;
        buff->data = realloc(buff->data, buff->cap);
    }

    buff->data[buff->len++] = c;
}

SV BufferMakeSV(Buffer* buff) {
    char* svContents = malloc((buff->len + 1) * sizeof(char));
    strncpy(svContents, buff->data, buff->len);
    svContents[buff->len] = '\0';

    SV sv = {
        .str = svContents,
        .len = buff->len
    };

    return sv;
}

void BufferReset(Buffer* buff) {
    buff->len = 0;
    buff->cap = INIT_CAPACITY;
    buff->data = realloc(buff->data, buff->cap);
}

void BufferFree(Buffer* buff) {
    free(buff->data);
    free(buff);
}