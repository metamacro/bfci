#ifndef DATA_H
#define DATA_H

#include <bfci/memory.h>

#include <utarray.h>
#include <uthash.h>
#include <utstack.h>

/* const defines */
/* conventional minimum number of cells based on Urban Muller's compiler */
#define PROGRAM_DATA_DEFAULT_LEN   30000
#define PROGRAM_DATA_GROWTH_FACTOR 1.5

/* helper macros */
#define UT_ARRAY_ITER(ARRAY, ELEM, CAST) \
    while (XNULL                         \
           != ((ELEM) = (CAST)utarray_next(ARRAY, ELEM)))

/* data */
static UT_icd
    char_icd
    = {
        sizeof(char),
        XNULL,
        XNULL,
        XNULL,
};

static UT_icd
    int8_t_icd
    = {
        sizeof(int8_t),
        XNULL,
        XNULL,
        XNULL,
};

typedef struct stack_s {
    int             pos;
    struct stack_s *next;
} stack_t;

typedef struct brackets_s {
    int            pos;
    int            matching_pos;
    UT_hash_handle hh;
} brackets_t;

typedef struct program_s {
    char     *progpath;
    UT_array *instructions;

    struct {
        UT_array   *intermediate;
        brackets_t *brackets;
    };

    struct {
        struct {
            UT_array *data;
            size_t    len;
        };
    };
} program_t;

/* array */
void
init_utarray_program_instructions(program_t *program);

void
free_utarray_program_instructions(program_t *program);

void
init_utarray_program_intermediate(program_t *program);

void
free_utarray_program_intermediate(program_t *program);

void
init_utarray_program_data(program_t *program);

void
extend_utarray_program_data(program_t *program);

void
free_utarray_program_data(program_t *program);

/* stack */
void
push_utstack_stack(stack_t **head, int pos);

void
pop_utstack_stack(stack_t **head);

/* hash map */
void
init_uthash_program_brackets(program_t *program);

void
init_uthash_program_brackets(program_t *program);

void
add_uthash_program_brackets(program_t *program, int pos, int matching_pos);

void
free_uthash_program_brackets(program_t *program);

#endif /* DATA_H */
