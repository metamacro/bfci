#ifndef BFCI_H
#define BFCI_H

#include <bfci/memory.h>
#include <utarray.h>
#include <uthash.h>

#include <stdint.h> /* uint32_t */

#define CMD_GT        '>'
#define CMD_LT        '<'
#define CMD_PLUS      '+'
#define CMD_MINUS     '-'
#define CMD_DOT       '.'
#define CMD_COMMA     ','
#define CMD_SB_OPEN   '['
#define CMD_SB_CLOSED ']'

#define UT_ARRAY_ITER(ARRAY, ELEM, CAST) \
    while (XNULL                         \
           != ((ELEM) = (CAST)utarray_next(ARRAY, ELEM)))

enum bfci_opcodes {
    OP_INC_DP      = 0x00,
    OP_DEC_DP      = 0x01,
    OP_INC_BYTE    = 0x02,
    OP_DEC_BYTE    = 0x03,
    OP_OUT_BYTE    = 0x04,
    OP_IN_BYTE     = 0x05,
    OP_JMP_FORWARD = 0x06,
    OP_JMP_BACK    = 0x07,
    OP_LEN         = 0x08,
};

typedef enum bfci_status {
    SUCCESS = 0x00,
    FAILURE = 0x01,
} bfci_status_t;

typedef struct bracket_s {
    int pc_pos;
    int type;
} bracket_t;

typedef struct brackets_s {
    bracket_t      bracket;
    bracket_t      matching_bracket;
    UT_hash_handle hh;
} brackets_t;

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

typedef struct program_s {
    char     *progpath;
    UT_array *data;

    struct {
        uint32_t  pc;
        UT_array *intermediate;
    };
} program_t;

void
init_utarray_program_data(program_t *program);

void
init_utarray_program_intermediate(program_t *program);

void
free_program(program_t *program);

#endif /* BFCI_H */
