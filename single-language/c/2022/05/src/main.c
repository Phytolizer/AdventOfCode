#include <advent/macro.h>
#include <advent/parse.h>
#include <advent/read.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct state {
    int     part;
    bool    parsing_crates;
    char**  crates;
    size_t  num_crates;
    size_t* stack_sizes;
};

static char* topof(char* stack, size_t stack_size)
{
    for (size_t i = stack_size; i > 0; i--) {
        if (stack[i - 1] != ' ') {
            return &stack[i];
        }
    }
    return &stack[0];
}

static void apply_motion(struct state* state, int crate_count, int source_stack, int target_stack)
{
    switch (state->part) {
        case 1:
            for (int i = 0; i < crate_count; i++) {
                char* src = topof(state->crates[source_stack - 1], state->stack_sizes[source_stack - 1]) - 1;
                assert(src >= state->crates[source_stack - 1]);
                char* dst = topof(state->crates[target_stack - 1], state->stack_sizes[target_stack - 1]);
                if ((size_t)(dst - state->crates[target_stack - 1]) == state->stack_sizes[target_stack - 1]) {
                    state->stack_sizes[target_stack - 1]++;
                    state->crates[target_stack - 1] = realloc(state->crates[target_stack - 1], state->stack_sizes[target_stack - 1] + 1);
                    dst = &state->crates[target_stack - 1][state->stack_sizes[target_stack - 1]];
                }
                *dst = *src;
                *src = ' ';
            }
            break;
        case 2:
            assert(false && "TODO");
            break;
        default:
            assert(false && "unreachable");
            break;
    }
}

static void line(void* user, const char* line, size_t len)
{
    if (len == 0) {
        return;
    }
    struct state* state = user;
    if (state->crates == NULL) {
        state->parsing_crates = true;
        // NOTE: this takes advantage of trailing whitespace in the input file.
        //
        // adding 3 is to perform a ceiling divide
        state->num_crates = (len - 1 + 3) / 4;
        size_t crates_sz = state->num_crates * sizeof(char*);
        state->crates = malloc(crates_sz);
        memset(state->crates, 0, crates_sz);
        size_t stacks_sz = state->num_crates * sizeof(size_t);
        state->stack_sizes = malloc(stacks_sz);
        memset(state->stack_sizes, 0, stacks_sz);
    }

    // BUG: currently reallocated lines are NOT entirely overwritten!
    if (state->parsing_crates) {
        for (size_t line_idx = 1; line_idx < len; line_idx += 4) {
            if (line[line_idx] == '1') {
                state->parsing_crates = false;
                return;
            }
            size_t crate_idx = (line_idx - 1) / 4;
            size_t stack_size = state->stack_sizes[crate_idx];
            state->crates[crate_idx] = realloc(state->crates[crate_idx], (stack_size + 1));
            memmove(state->crates[crate_idx] + 1, state->crates[crate_idx], stack_size);
            state->crates[crate_idx][0] = line[line_idx];
            state->stack_sizes[crate_idx]++;
        }
    } else {
        const char* mover = line;
        TAG_OR_DIE(&mover, "move ");
        struct int_with_tail crate_count = read_int(mover);
        mover = crate_count.tail;
        TAG_OR_DIE(&mover, " from ");
        struct int_with_tail source_stack = read_int(mover);
        mover = source_stack.tail;
        TAG_OR_DIE(&mover, " to ");
        struct int_with_tail target_stack = read_int(mover);
        mover = target_stack.tail;
        assert((size_t)(mover - line) == len);

        apply_motion(state, crate_count.value, source_stack.value, target_stack.value);
    }
}

static void part1_finish(void* user)
{
    struct state* state = user;
    for (size_t i = 0; i < state->num_crates; i++) {
        const char* top = topof(state->crates[i], state->stack_sizes[i]) - 1;
        assert(top >= state->crates[i]);
        putchar(*top);
    }
    putchar('\n');
    for (size_t i = 0; i < state->num_crates; i++) {
        free(state->crates[i]);
    }
    free(state->crates);
    free(state->stack_sizes);
}

static void part1(const char* path)
{
    struct state state = {
        .part = 1,
    };
    read_file(path, line, part1_finish, &state);
}

static void solve_file(const char* path)
{
    part1(path);
}

ADVENT_MAIN

