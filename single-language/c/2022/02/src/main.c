#include <advent/macro.h>
#include <advent/read.h>
#include <assert.h>
#include <stdio.h>

struct state {
    int score;
};

enum {
    irock,
    ipaper,
    iscissors,
    rock = 1,
    paper = 2,
    scissors = 3,
    lose = 0,
    draw = 3,
    win = 6,
};

static const int scores[] = {
    [3 * irock     + irock    ] = rock     + draw,
    [3 * irock     + ipaper   ] = paper    + win,
    [3 * irock     + iscissors] = scissors + lose,
    [3 * ipaper    + irock    ] = rock     + lose,
    [3 * ipaper    + ipaper   ] = paper    + draw,
    [3 * ipaper    + iscissors] = scissors + win,
    [3 * iscissors + irock    ] = rock     + win,
    [3 * iscissors + ipaper   ] = paper    + lose,
    [3 * iscissors + iscissors] = scissors + draw,
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
        [irock     + lose] = iscissors,
        [irock     + draw] = irock,
        [irock     + win ] = ipaper,
        [ipaper    + lose] = irock,
        [ipaper    + draw] = ipaper,
        [ipaper    + win ] = iscissors,
        [iscissors + lose] = ipaper,
        [iscissors + draw] = iscissors,
        [iscissors + win ] = irock,
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

