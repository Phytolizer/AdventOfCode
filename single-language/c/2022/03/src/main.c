#include <advent/macro.h>
#include <advent/read.h>
#include <assert.h>
#include <stdbool.h>
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

enum {
    CHAR_COUNT = 52,
    GROUPS = 3,
};

typedef bool group[CHAR_COUNT];

struct part2_state {
    size_t group_idx;
    group prev_groups[GROUPS];
    int sum;
};

static void part2_line(void* user, const char* line, size_t len)
{
    struct part2_state* state = user;
    memset(state->prev_groups[state->group_idx], 0, sizeof(group));
    for (size_t i = 0; i < len; i++) {
        assert(priority(line[i]) > 0);
        state->prev_groups[state->group_idx][priority(line[i]) - 1] = true;
    }
    if (state->group_idx == GROUPS - 1) {
        for (size_t i = 0; i < CHAR_COUNT; i++) {
            bool all = true;
            for (size_t j = 0; j < GROUPS; j++) {
                if (!state->prev_groups[j][i]) {
                    all = false;
                    break;
                }
            }
            if (all) {
                state->sum += i + 1;
            }
        }
        state->group_idx = 0;
    } else {
        state->group_idx += 1;
    }
}

static void part2_finish(void* user)
{
    struct part2_state* state = user;
    printf("Part 2: %d\n", state->sum);
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

