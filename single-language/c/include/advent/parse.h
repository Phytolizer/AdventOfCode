#ifndef ADVENT_PARSE_H_
#define ADVENT_PARSE_H_

int read_int_or_die(const char* text);

struct int_with_tail {
    int value;
    const char* tail;
};

struct int_with_tail read_int(const char* text);

#endif  // ADVENT_PARSE_H_

