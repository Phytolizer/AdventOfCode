#include "advent/read.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void read_file(const char* path, line_callback* line_cb, finish_callback* finish_cb, void* user)
{
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        fprintf(stderr, "couldn't open %s\n", path);
        perror("fopen");
        exit(1);
    }
    char* line = NULL;
    size_t cap = 0;

    while (true) {
        errno = 0;
        ssize_t len = getline(&line, &cap, f);
        if (len == -1) {
            if (errno) {
                perror("getline");
                free(line);
                fclose(f);
                exit(1);
            }
            break;
        }

        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = 0;
            len -= 1;
        }

        line_cb(user, line, len);
    }
    free(line);
    fclose(f);
    finish_cb(user);
}

