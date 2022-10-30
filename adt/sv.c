#include "sv.h"

#include <string.h>

SV NewSVFromCStr(const char* cstr) {
    SV sv = {
        .str=cstr,
        .len=strlen(cstr)
    };

    return sv;
}

bool SVEqual(SV a, SV b) {
    if (a.len != b.len) {
        return false;
    }

    return strncmp(a.str, b.str, a.len) == 0;
}