#include "advent/parse.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int read_int_or_die(const char* text)
{
    errno = 0;
    char* endp;
    long val = strtol(text, &endp, 10);
    if (errno != 0) {
        perror("strtol");
        exit(1);
    }
    if (val > INT_MAX || val < 0) {
        fputs("number is too large or too small", stderr);
        exit(1);
    }
    if (*endp != 0) {
        fputs("line is not a number", stderr);
        exit(1);
    }
    return (int)val;
}


