#include "error.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void Error(const char* msg, ...) {
    printf("error: ");

    va_list args;
    va_start(args, msg);

    vprintf(msg, args);

    va_end(args);

    putchar('\n');

    exit(1);
}