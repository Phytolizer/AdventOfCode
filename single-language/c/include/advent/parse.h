#ifndef ADVENT_PARSE_H_
#define ADVENT_PARSE_H_

#include <stdbool.h>
#include <string.h>

int read_int_or_die(const char* text);

struct int_with_tail {
    int value;
    const char* tail;
};

struct int_with_tail read_int(const char* text);

bool tag(const char** p_text, const char* lit, size_t lit_len);
#define TAG(text, lit) tag((text), (lit), sizeof(lit) - 1)
void tag_or_die(const char** p_text, const char* lit, size_t lit_len);
#define TAG_OR_DIE(text, lit) tag_or_die((text), (lit), sizeof(lit) - 1)

#endif  // ADVENT_PARSE_H_

