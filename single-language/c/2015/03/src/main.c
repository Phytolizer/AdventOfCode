#include <advent/macro.h>
#include <advent/read.h>
#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct pos {
    int x;
    int y;
};

struct part1_state {
    struct pos* visited;
    size_t len;
    size_t cap;
    struct pos pos;
};

static bool pos_eq(struct pos a, struct pos b)
{
    return a.x == b.x and a.y == b.y;
}

static void part1_push(struct part1_state* state, struct pos pos)
{
    if (state->len == state->cap)
    {
        state->cap = state->cap * 2 + 1;
        struct pos* temp = realloc(state->visited, state->cap * sizeof(struct pos));
        assert(temp != NULL);
        state->visited = temp;
    }
    for (size_t i = 0; i < state->len; i++) {
        if (pos_eq(state->visited[i], pos)) {
            return;
        }
    }
    state->visited[state->len++] = pos;
}

static void part1_line(void* user, const char* line, size_t len)
{
    struct part1_state* state = user;
    for (size_t i = 0; i < len; i++) {
        switch (line[i]) {
            case '<':
                state->pos.x--;
                break;
            case 'v':
                state->pos.y++;
                break;
            case '>':
                state->pos.x++;
                break;
            case '^':
                state->pos.y--;
                break;
            default:
                continue;
        }
        part1_push(state, state->pos);
    }
}

static void part1_finish(void* user)
{
    struct part1_state* state = user;
    printf("Part 1: %zu\n", state->len);
}

static void part1(const char* path)
{
    struct part1_state state = {0};
    part1_push(&state, state.pos);
    read_file(path, part1_line, part1_finish, &state);
    free(state.visited);
}

struct part2_state {
    struct part1_state history;
    struct pos robo_santa;
    bool robo;
};

static void part2_line(void* user, const char* line, size_t len)
{
    struct part2_state* state = user;
    for (size_t i = 0; i < len; i++) {
        struct pos* who = state->robo ? &state->robo_santa : &state->history.pos;
        switch (line[i]) {
            case '<':
                who->x--;
                break;
            case 'v':
                who->y++;
                break;
            case '>':
                who->x++;
                break;
            case '^':
                who->y--;
                break;
            default:
                continue;
        }
        part1_push(&state->history, *who);
        state->robo = !state->robo;
    }
}

static void part2_finish(void* user)
{
    struct part2_state* state = user;
    printf("Part 2: %zu\n", state->history.len);
}

static void part2(const char* path)
{
    struct part2_state state = {0};
    part1_push(&state.history, state.history.pos);
    read_file(path, part2_line, part2_finish, &state);
    free(state.history.visited);
}

static void solve_file(const char* path)
{
    part1(path);
    part2(path);
}

ADVENT_MAIN
