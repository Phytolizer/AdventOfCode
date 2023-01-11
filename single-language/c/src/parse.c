#include "advent/parse.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int read_int_or_die(const char* text)
{
    struct int_with_tail with_tail = read_int(text);
    if (*with_tail.tail != 0) {
        fputs("line is not a number", stderr);
        exit(1);
    }
    return with_tail.value;
}

struct int_with_tail read_int(const char* text)
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
    return (struct int_with_tail){
        .value = (int)val,
        .tail = endp,
    };
}

bool tag(const char** p_text, const char* lit, size_t lit_len)
{
    if (memcmp(*p_text, lit, lit_len) != 0) {
        return false;
    }

    *p_text += lit_len;
    return true;
}

void tag_or_die(const char** p_text, const char* lit, size_t lit_len)
{
    if (!tag(p_text, lit, lit_len)) {
        fprintf(stderr, "missing tag '%.*s'\n", (int)lit_len, lit);
        exit(1);
    }
}

