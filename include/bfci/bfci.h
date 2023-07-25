#ifndef BFCI_H
#define BFCI_H

#include <bfci/data.h>
#include <bfci/memory.h>

#include <stdint.h> /* uint32_t */

#define CMD_GT        '>'
#define CMD_LT        '<'
#define CMD_PLUS      '+'
#define CMD_MINUS     '-'
#define CMD_DOT       '.'
#define CMD_COMMA     ','
#define CMD_SB_OPEN   '['
#define CMD_SB_CLOSED ']'

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

bfci_status_t
bfci_init_program(program_t *program, int argc, const char *argv[]);

void
bfci_free_program(program_t *program);

#endif /* BFCI_H */
