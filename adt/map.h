#ifndef _MAP_H_
#define _MAP_H_

#include "sv.h"

// Map represents a simple hash table using strings as keys.
typedef struct Map Map;

// NewMap creates a new map.
Map* NewMap();

// MapGet gets a value from the map corresponding to key if such a value exists.
void* MapGet(Map* map, SV key);

// MapPut puts a new key-value pair into the map.  This will overwrite any
// pre-existing key-value pair with the same key.
void MapPut(Map* map, SV key, void* value);

// MapRemove removes a key from a map and returns its value.
void* MapRemove(Map* map, SV key);

// MapLen returns the length of the map.
size_t MapLen(Map* map);

#endif