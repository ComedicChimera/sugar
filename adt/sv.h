#ifndef _SV_H_
#define _SV_H_

#include <stdbool.h>

// SV represents a string view.
typedef struct {
    // The internal C-string buffer of the string view.
    const char* str;

    // The length of the string view.
    size_t len;
} SV;

// NewSVFromCStr creates a new string view from a C string.
SV NewSVFromCStr(const char* cstr);

// SVEqual return whether two string views are equal.
bool SVEqual(SV a, SV b);

#endif