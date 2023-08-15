#ifndef DATA_H
#define DATA_H

#include <bfci/memory.h>

#include <utarray.h>
#include <uthash.h>

/* helper macros */
#define UT_ARRAY_ITER(ARRAY, ELEM, CAST) \
    while (XNULL                         \
           != ((ELEM) = (CAST)utarray_next(ARRAY, ELEM)))

/* structs */
static UT_icd
    char_icd
    = {
        sizeof(char),
        XNULL,
        XNULL,
        XNULL,
};

static UT_icd
    uint8_t_icd
    = {
        sizeof(uint8_t),
        XNULL,
        XNULL,
        XNULL,
};

typedef struct bracket_s {
    int pc_pos;
    int type;
} bracket_t;

typedef struct brackets_s {
    bracket_t      bracket;
    bracket_t      matching_bracket;
    UT_hash_handle hh;
} brackets_t;

typedef struct program_s {
    char     *progpath;
    UT_array *instructions;

    struct {
        uint32_t  pc;
        UT_array *data;
    };

    struct {
        UT_array *intermediate;
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

#endif /* DATA_H */
