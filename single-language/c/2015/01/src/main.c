#include <advent/macro.h>
#include <advent/read.h>
#include <iso646.h>
#include <stdio.h>

struct part2_state {
    int floor;
    int idx;
    int result;
};

static void part2_line(void* user, const char* line, size_t len)
{
    struct part2_state* state = user;
    for (size_t i = 0; i < len; i++) {
        switch (line[i]) {
            case '(':
                state->floor++;
                break;
            case ')':
                state->floor--;
                if (state->result == 0 and state->floor < 0) {
                    state->result = state->idx;
                }
                break;
            default:
                break;
        }
        state->idx++;
    }
}

static void part2_finish(void* user)
{
    struct part2_state* state = user;
    printf("Part 2: %d\n", state->result);
}

static void part2(const char* path)
{
    struct part2_state state = {
        .idx = 1,
    };
    read_file(path, part2_line, part2_finish, &state);
}

struct part1_state {
    int floor;
};

static void part1_line(void* user, const char* line, size_t len)
{
    struct part1_state* state = user;
    for (size_t i = 0; i < len; i++) {
        switch (line[i]) {
            case '(':
                state->floor++;
                break;
            case ')':
                state->floor--;
                break;
            default:
                break;
        }
    }
}

static void part1_finish(void* user)
{
    struct part1_state* state = user;
    printf("Part 1: %d\n", state->floor);
}

static void part1(const char* path)
{
    struct part1_state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

static void solve_file(const char* path)
{
    part1(path);
    part2(path);
}

ADVENT_MAIN
