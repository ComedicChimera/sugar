#include "map.h"

#include <stdlib.h>

// The FNV-64a hash constants.
#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x100000001b3

// hash computes the FNV-64a hash.
static size_t hash(SV sv) {
    size_t h = FNV_OFFSET_BASIS;

    for (int i = 0; i < sv.len; i++) {
        h ^= sv.str[i];
        h *= FNV_PRIME;
    }

    return h;
}

/* -------------------------------------------------------------------------- */

// NOTE: This map is implemented using open addressing with simple linear
// probing. It is not the most efficient implementation, but it works and has
// decent performance so that's really what matters :)

#define INIT_CAPACITY 16
#define GROWTH_FACTOR 2
#define MAX_LOAD_FACTOR 0.7
#define MAX_ELEM_DENSITY 0.35

#define TOMBSTONE (void*)(-1)

typedef struct Map {
    // The keys of the map.
    SV** keys;

    // The values of the map.
    void** values;

    // The number of elements in the map.
    size_t len;

    // The number of table locations which are current used.  This includes both
    // elements and tombstones.
    size_t used;

    // The capacity of the map.
    size_t cap;
} Map;

Map* NewMap() {
    Map* m = malloc(sizeof(Map));

    m->keys = calloc(INIT_CAPACITY, sizeof(SV*));
    m->values = calloc(INIT_CAPACITY, sizeof(void*));
    m->len = 0;
    m->used = 0;
    m->cap = INIT_CAPACITY;

    return m;
}

size_t MapLen(Map* m) {
    return m->len;
}

void* MapGet(Map* m, SV key) {
    size_t i = hash(key) % m->cap;

    SV* kptr;
    for (; (kptr = m->keys[i]) != NULL; i = (i + 1) % m->cap) {
        if (kptr != TOMBSTONE && SVEqual(*kptr, key)) {
            return m->values[i];
        }
    }

    return NULL;
}

// mapGrow increases the capacity of the map and rebalances its internal hash
// table appropriately.  It also removes all tombstones from the map thereby
// reducing the load factor of the map.
void mapGrow(Map* m) {
    size_t newCap = (m->len > m->cap * MAX_ELEM_DENSITY) ? m->cap * GROWTH_FACTOR : m->cap;

    SV** newKeys = calloc(newCap, sizeof(SV*));
    void** newValues = calloc(newCap, sizeof(void*));

    for (int i = 0; i < m->cap; i++) {
        SV* kptr = m->keys[i];

        if (kptr == NULL || kptr == TOMBSTONE)
            continue;

        size_t j = hash(*kptr) % newCap;
        for (;; j = (j + 1) % newCap) {
            if (newKeys[j] == NULL) {
                newKeys[j] = kptr;
                newValues[j] = m->values[i];
                break;
            }
        }
    }

    m->keys = newKeys;
    m->values = newValues;
    m->used = m->len;
    m->cap = newCap;
}

void MapPut(Map* m, SV key, void* value) {
    if (m->used > m->cap * MAX_LOAD_FACTOR)
        mapGrow(m);
    
    size_t i = hash(key) % m->cap;

    for (;; i = (i + 1) % m->cap) {
        SV* kptr = m->keys[i];

        if (kptr == NULL || kptr == TOMBSTONE) {
            m->len++;
            if (kptr == NULL)
                m->used++;

            kptr = malloc(sizeof(SV));
            *kptr = key;

            m->keys[i] = kptr;
            m->values[i] = value;
            m->len++;

            return;
        }
    }    
}

void* MapRemove(Map* m, SV key) {
    size_t i = hash(key) % m->cap;

    SV* kptr;
    for (; (kptr = m->keys[i]) != NULL; i = (i + 1) % m->cap) {
        if (kptr != TOMBSTONE && SVEqual(*kptr, key)) {
            m->len--;

            m->keys[i] = TOMBSTONE;

            free(kptr);

            return m->values[i];
        }
    }

    return NULL;
}
