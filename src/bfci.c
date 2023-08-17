#include <bfci/bfci.h>
#include <bfci/data.h>
#include <bfci/debug.h>
#include <bfci/intermediate.h>
#include <bfci/io.h>
#include <bfci/utils.h>
#include <stdio.h>

bfci_status_t
bfci_init_program(program_t *program, int argc, const char *argv[])
{
    int rc = SUCCESS;

    RC_GOTO_IF_NEQ(SUCCESS,
                   argparse(argc, argv, program),
                   error);

    RC_GOTO_IF_NEQ(SUCCESS,
                   read_program(program),
                   error);

    RC_GOTO_IF_NEQ(SUCCESS,
                   compile_intermediate(program),
                   error);

    goto out;
error:
    rc = FAILURE;
out:
    TRACE("%d", rc);
    return rc;
}

static int
get_matching_bracket_pos(program_t *program, int pos)
{
    brackets_t *el = XNULL;

    HASH_FIND_INT(program->brackets, &pos, el);

    return el->matching_pos;
}

bfci_status_t
bfci_run_program(program_t *program)
{
    int      rc     = SUCCESS;
    size_t   pc     = 0;
    size_t   pc_max = 0;
    size_t   dp     = 0;
    int8_t  *de     = XNULL;
    uint8_t *cmd    = 0;

    pc_max = utarray_len(program->intermediate);
    init_utarray_program_data(program);

    while (pc < pc_max) {
        if (dp > program->len) extend_utarray_program_data(program);

        cmd = utarray_eltptr(program->intermediate, pc);
        de  = utarray_eltptr(program->data, dp);

        switch (*cmd) {
        case OP_INC_DP:
            dp++;
            break;
        case OP_DEC_DP:
            dp--;
            break;
        case OP_INC_BYTE:
            (*de)++;
            break;
        case OP_DEC_BYTE:
            (*de)--;
            break;
        case OP_OUT_BYTE:
            putchar(*de);
            break;
        case OP_IN_BYTE:
            *de = getchar();
            break;
        case OP_JMP_FORWARD:
            if (0 == *de) {
                pc = get_matching_bracket_pos(program, pc);
            }
            break;
        case OP_JMP_BACK:
            if (0 != *de) {
                pc = get_matching_bracket_pos(program, pc);
            }
            break;
        default:
            TRACE("%c", *cmd);
            goto error;
        }

        pc++;
    }

    goto out;
error:
    rc = FAILURE;
out:
    TRACE("%d", rc);
    return rc;
}

void
bfci_free_program(program_t *program)
{
    TRACE("%p", (void *)program->progpath);
    XFREE(program->progpath);

    TRACE("%p", (void *)program->instructions);
    RUN_IF_NON_NULL(program->instructions,
                    free_utarray_program_instructions(program));

    TRACE("%p", (void *)program->intermediate);
    RUN_IF_NON_NULL(program->intermediate,
                    free_utarray_program_intermediate(program));

    TRACE("%p", (void *)program->brackets);
    RUN_IF_NON_NULL(program->brackets,
                    free_uthash_program_brackets(program));

    TRACE("%p", (void *)program->data);
    RUN_IF_NON_NULL(program->data,
                    free_utarray_program_data(program));
}
