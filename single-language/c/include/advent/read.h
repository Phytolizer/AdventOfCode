#ifndef ADVENT_READ_H_
#define ADVENT_READ_H_

#include <stddef.h>

typedef void line_callback(void* user, const char* line, size_t len);
typedef void finish_callback(void* user);

void read_file(const char* path, line_callback* line_cb, finish_callback* finish_cb, void* user);

#endif  // ADVENT_READ_H_
