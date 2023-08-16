#include <bfci/data.h>
#include <bfci/debug.h>
#include <bfci/intermediate.h>
#include <bfci/utils.h>

#include <utarray.h>
#include <utstack.h>

static void
add_matching_brackets(program_t *program, int pos, int matching_pos)
{
    add_uthash_program_brackets(program, pos, matching_pos);
    add_uthash_program_brackets(program, matching_pos, pos);
}

bfci_status_t
build_program_brackets_hashmap(program_t *program)
{
    int      rc   = SUCCESS;
    int      pc   = 0;
    uint8_t *cmd  = XNULL;
    stack_t *head = XNULL;

    init_uthash_program_brackets(program);

    UT_ARRAY_ITER(program->intermediate, cmd, uint8_t *)
    {
        switch (*cmd) {
        case OP_JMP_FORWARD:
            push_utstack_stack(&head, pc);
            break;
        case OP_JMP_BACK:
            /* non matching closed bracket */
            //RC_GOTO_IF_NEQ(false,
                           //STACK_EMPTY(head),
                           //error);

            add_matching_brackets(program, STACK_TOP(head)->pos, pc);
            pop_utstack_stack(&head);
            break;
        }
        pc++;
    }
    brackets_t *el  = XNULL;
    brackets_t *tmp = XNULL;

    HASH_ITER(hh, program->brackets, el, tmp)
    {
        printf("pair %d %d\n", el->pos, el->matching_pos);
    }

    /* non matching open bracket */
    RC_GOTO_IF_NEQ(true,
                   STACK_EMPTY(head),
                   error);

    goto out;
error:
    rc = FAILURE;
out:
    TRACE("%d", rc);
    return rc;
}

bfci_status_t
compile_intermediate(program_t *program)
{
    int     rc  = SUCCESS;
    char   *cp  = XNULL;
    uint8_t cmd = 0;

    init_utarray_program_intermediate(program);

    UT_ARRAY_ITER(program->instructions, cp, char *)
    {
        switch (*cp) {
        case CMD_GT:
            cmd = OP_INC_DP;
            break;
        case CMD_LT:
            cmd = OP_DEC_DP;
            break;
        case CMD_PLUS:
            cmd = OP_INC_BYTE;
            break;
        case CMD_MINUS:
            cmd = OP_DEC_BYTE;
            break;
        case CMD_DOT:
            cmd = OP_OUT_BYTE;
            break;
        case CMD_COMMA:
            cmd = OP_IN_BYTE;
            break;
        case CMD_SB_OPEN:
            cmd = OP_JMP_FORWARD;
            break;
        case CMD_SB_CLOSED:
            cmd = OP_JMP_BACK;
            break;
        default:
            TRACE("%c", *cp);
            goto error;
        }
        utarray_push_back(program->intermediate, &cmd);
    }

    RC_GOTO_IF_NEQ(SUCCESS,
                   build_program_brackets_hashmap(program),
                   error);

    goto out;
error:
    rc = FAILURE;
out:
    TRACE("%d", rc);
    return rc;
}
