#include <advent/macro.h>
#include <advent/read.h>
#include <assert.h>
#include <stdio.h>

struct state {
    int score;
};

static const int scores[] = {
    [3 * 0 + 0] = 1 + 3,
    [3 * 0 + 1] = 2 + 6,
    [3 * 0 + 2] = 3 + 0,
    [3 * 1 + 0] = 1 + 0,
    [3 * 1 + 1] = 2 + 3,
    [3 * 1 + 2] = 3 + 6,
    [3 * 2 + 0] = 1 + 6,
    [3 * 2 + 1] = 2 + 0,
    [3 * 2 + 2] = 3 + 3,
};

static void part1_line(void* user, const char* line, size_t len)
{

    if (len != 3) {
        return;
    }
    struct state* state = user;
    char opponent = line[0];
    assert(line[1] == ' ');
    char self = line[2];
    int opponent_i = opponent - 'A';
    int self_i = self - 'X';
    int score = scores[3 * opponent_i + self_i];
    state->score += score;
}

static void part1_finish(void* user)
{
    struct state* state = user;
    printf("Part 1: %d\n", state->score);
}

static void part1(const char* path)
{
    struct state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

static void part2_line(void* user, const char* line, size_t len) {
    static const int moves[] = {
        [0 + 3 * 0] = 2,
        [0 + 3 * 1] = 0,
        [0 + 3 * 2] = 1,
        [1 + 3 * 0] = 0,
        [1 + 3 * 1] = 1,
        [1 + 3 * 2] = 2,
        [2 + 3 * 0] = 1,
        [2 + 3 * 1] = 2,
        [2 + 3 * 2] = 0,
    };

    if (len != 3) {
        return;
    }
    struct state* state = user;
    char opponent = line[0];
    assert(line[1] == ' ');
    char self = line[2];
    int opponent_i = opponent - 'A';
    int self_i = self - 'X';
    int move = moves[opponent_i + 3 * self_i];
    int score = scores[3 * opponent_i + move];
    state->score += score;
}

static void part2_finish(void* user)
{
    struct state* state = user;
    printf("Part 2: %d\n", state->score);
}

static void part2(const char* path)
{
    struct state state = {0};
    read_file(path, part2_line, part2_finish, &state);
}

static void solve_file(const char* path)
{
    part1(path);
    part2(path);
}

ADVENT_MAIN

