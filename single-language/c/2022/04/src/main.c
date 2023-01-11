#include <advent/macro.h>
#include <advent/parse.h>
#include <advent/read.h>
#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

struct state {
    int count;
};

struct range {
    int begin;
    int end;
    const char* tail;
};

static struct range parse_range(const char* line)
{
    struct int_with_tail parser = read_int(line);
    struct range range = {
        .begin = parser.value,
    };
    assert(*parser.tail == '-');
    parser = read_int(parser.tail + 1);
    range.end = parser.value;
    range.tail = parser.tail;
    return range;
}

static bool contains(struct range big, struct range small)
{
    return big.begin <= small.begin and big.end >= small.end;
}

static void part1_line(void* user, const char* line, size_t len)
{
    struct state* state = user;
    struct range first = parse_range(line);
    assert(*first.tail == ',');
    struct range second = parse_range(first.tail + 1);
    assert((size_t)(second.tail - line) == len);
    if (contains(first, second) or contains(second, first)) {
        state->count++;
    }
}

static void part1_finish(void* user)
{
    struct state* state = user;
    printf("Part 1: %d\n", state->count);
}

static void part1(const char* path)
{
    struct state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

static bool overlaps(struct range a, struct range b)
{
    return a.begin <= b.begin and a.end >= b.begin or
           b.begin <= a.begin and b.end >= a.begin;
}

static void part2_line(void* user, const char* line, size_t len)
{
    struct state* state = user;
    struct range first = parse_range(line);
    assert(*first.tail == ',');
    struct range second = parse_range(first.tail + 1);
    assert((size_t)(second.tail - line) == len);
    if (overlaps(first, second)) {
        state->count++;
    }
}

static void part2_finish(void* user)
{
    struct state* state = user;
    printf("Part 2: %d\n", state->count);
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

