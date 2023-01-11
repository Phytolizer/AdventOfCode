#include <advent/macro.h>
#include <advent/parse.h>
#include <advent/read.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

struct state {
    bool    parsing_crates;
    char**  crates;
    size_t  num_crates;
    size_t* stack_sizes;
};

static void part1_line(void* user, const char* line, size_t len)
{
    struct state* state = user;
    if (state->crates == NULL) {
        // NOTE: this takes advantage of trailing whitespace in the input file.
        state->num_crates = (len - 1) / 4;
    }
}

static void part1_finish(void* user)
{
}

static void part1(const char* path)
{
    struct state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

static void solve_file(const char* path)
{
    part1(path);
}

ADVENT_MAIN

