#include <advent/macro.h>
#include <advent/read.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int priority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 26 + 1;
    }
    return 0;
}

struct part1_state {
    int sum;
};

enum {
    MAX_LINE = 100,
};

static void part1_line(void* user, const char* line, size_t len)
{
    struct part1_state* state = user;
    char common = 0;
    for (size_t i = len / 2; i < len; i++) {
        if (memchr(line, line[i], len / 2)) {
            common = line[i];
            break;
        }
    }
    assert(common != 0);
    state->sum += priority(common);
}

static void part1_finish(void* user)
{
    struct part1_state* state = user;
    printf("Part 1: %d\n", state->sum);
}

static void part1(const char* path)
{
    struct part1_state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

struct part2_state {
    size_t group_idx;
    char prev_groups[MAX_LINE][2];
    int sum;
};

static void part2_line(void* user, const char* line, size_t len)
{
    struct part2_state* state = user;
    if (state->group_idx < 2) {
        memcpy(state->prev_groups[state->group_idx], line, len);
        state->prev_groups[state->group_idx][len] = 0;
    } else {
    }
}

static void part2_finish(void* user)
{
    struct part2_state* state = user;
    printf("Part 1: %d\n", state->sum);
}

static void part2(const char* path)
{
    struct part2_state state = {0};
    read_file(path, part2_line, part2_finish, &state);
}

static void solve_file(const char* path)
{
    part1(path);
}

ADVENT_MAIN

