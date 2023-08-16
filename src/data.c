#include "bfci/memory.h"
#include <bfci/data.h>
#include <bfci/debug.h>

/* array */
void
init_utarray_program_instructions(program_t *program)
{
    utarray_new(program->instructions, &char_icd);
}

void
free_utarray_program_instructions(program_t *program)
{
    utarray_free(program->instructions);
}

void
init_utarray_program_intermediate(program_t *program)
{
    utarray_new(program->intermediate, &uint8_t_icd);
}

void
free_utarray_program_intermediate(program_t *program)
{
    utarray_free(program->intermediate);
}

void
init_utarray_program_data(program_t *program)
{
    utarray_new(program->data, &uint8_t_icd);
    program->len = PROGRAM_DATA_DEFAULT_LEN;
    utarray_resize(program->data, program->len);
}

void
extend_utarray_program_data(program_t *program)
{
    int len      = utarray_len(program->data);
    program->len = (int)len * PROGRAM_DATA_GROWTH_FACTOR;
    utarray_resize(program->data, program->len);
}

void
free_utarray_program_data(program_t *program)
{
    utarray_free(program->data);
}

/* stack */
void
push_utstack_stack(stack_t **head, int pos)
{
    stack_t *el = xmalloc(sizeof(stack_t));
    el->pos     = pos;
    STACK_PUSH(*head, el);
}

void
pop_utstack_stack(stack_t **head)
{
    stack_t *elt = XNULL;

    TRACE("%p", (void *)*head);
    if (STACK_EMPTY(*head)) return;

    STACK_POP(*head, elt);
    XFREE(elt);
}

/* hash map */
void
init_uthash_program_brackets(program_t *program)
{
    program->brackets = XNULL;
}

void
add_uthash_program_brackets(program_t *program, int pos, int matching_pos)
{
    brackets_t *el = XNULL;

    HASH_FIND_INT(program->brackets, &pos, el);
    /* doesn't exist? */
    if (XNULL == el) {
        el               = xmalloc(sizeof(brackets_t));
        /* set key */
        el->pos          = pos;
        el->matching_pos = matching_pos;
        HASH_ADD_INT(program->brackets, pos, el);
    }
}

void
free_uthash_program_brackets(program_t *program)
{
    brackets_t *el  = XNULL;
    brackets_t *tmp = XNULL;

    HASH_ITER(hh, program->brackets, el, tmp)
    {
        HASH_DEL(program->brackets, el);
        XFREE(el);
    }
}
