#include <advent/macro.h>
#include <advent/parse.h>
#include <advent/read.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct part1_state {
    int acc;
    int max;
};

static void part1_line(void* user, const char* line, size_t len)
{
    struct part1_state* state = user;
    if (len == 0) {
        if (state->acc > state->max) {
            state->max = state->acc;
        }
        state->acc = 0;
    } else {
        state->acc += read_int_or_die(line);
    }
}

static void part1_finish(void* user)
{
    struct part1_state* state = user;
    if (state->acc > state->max) {
        state->max = state->acc;
    }
    printf("Part 1: %d\n", state->max);
}

static void part1(const char* path)
{
    struct part1_state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

struct part2_state {
    int acc;
    int maxes[3];
};

static void part2_update_maxes(struct part2_state* state)
{
    int* min = &state->maxes[0];
    for (size_t i = 1; i < 3; i++) {
        if (state->maxes[i] < *min) {
            min = &state->maxes[i];
        }
    }

    if (state->acc > *min) {
        *min = state->acc;
    }
    state->acc = 0;
}

static void part2_line(void* user, const char* line, size_t len)
{
    struct part2_state* state = user;
    if (len == 0) {
        part2_update_maxes(state);
    } else {
        state->acc += read_int_or_die(line);
    }
}

static void part2_finish(void* user)
{
    struct part2_state* state = user;
    part2_update_maxes(state);
    int sum = 0;
    for (size_t i = 0; i < 3; i++) {
        sum += state->maxes[i];
    }
    printf("Part 2: %d\n", sum);
}

static void part2(const char* path)
{
    struct part2_state state = {0};
    read_file(path, part2_line, part2_finish, &state);
}

static void solve_file(const char* path)
{
    part1(path);
    part2(path);
}

ADVENT_MAIN
