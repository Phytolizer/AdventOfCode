#include <advent/macro.h>
#include <advent/read.h>
#include <advent/parse.h>
#include <assert.h>
#include <stdio.h>

struct state {
    int total;
};

enum { L, W, H };

static int min3(int a, int b, int c)
{
    int result = a;
    if (b < result) result = b;
    if (c < result) result = c;
    return result;
}

static void part1_line(void* user, const char* line, size_t len)
{
    (void)len;
    struct state* state = user;
    const char* it = line;
    struct int_with_tail first = read_int(it);
    it = first.tail;
    assert(*it == 'x');
    it++;
    struct int_with_tail second = read_int(it);
    it = second.tail;
    assert(*it == 'x');
    it++;
    int dim[3] = {
        first.value,
        second.value,
        read_int_or_die(it),
    };
    int areas[3] = {
        2 * dim[L] * dim[W],
        2 * dim[W] * dim[H],
        2 * dim[H] * dim[L],
    };
    state->total += areas[0] + areas[1] + areas[2] +
                    min3(areas[0] / 2, areas[1] / 2, areas[2] / 2);
}

static void part1_finish(void* user)
{
    struct state* state = user;
    printf("Part 1: %d\n", state->total);
}

static void part1(const char* path)
{
    struct state state = {0};
    read_file(path, part1_line, part1_finish, &state);
}

static void part2_line(void* user, const char* line, size_t len)
{
    (void)len;
    struct state* state = user;
    const char* it = line;
    struct int_with_tail first = read_int(it);
    it = first.tail;
    assert(*it == 'x');
    it++;
    struct int_with_tail second = read_int(it);
    it = second.tail;
    assert(*it == 'x');
    it++;
    int dim[3] = {
        first.value,
        second.value,
        read_int_or_die(it),
    };
    int perims[] = {
        2 * (dim[0] + dim[1]),
        2 * (dim[1] + dim[2]),
        2 * (dim[2] + dim[0]),
    };
    state->total += min3(perims[0], perims[1], perims[2]);
    state->total += dim[0] * dim[1] * dim[2];
}

static void part2_finish(void* user)
{
    struct state* state = user;
    printf("Part 2: %d\n", state->total);
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
