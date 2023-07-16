#include "bfci/utils.h"
#include <bfci/bfci.h>
#include <bfci/debug.h>

void
free_program(program_t *program)
{
    TRACE("%p", (void *)program->progpath);
    XFREE(program->progpath);

    TRACE("%p", (void *)program->data);
    RUN_IF_NON_NULL(program->data,
                    utarray_free(program->data));

    TRACE("%p", (void *)program->intermediate);
    RUN_IF_NON_NULL(program->intermediate,
                    utarray_free(program->intermediate));
}

void
init_utarray_program_data(program_t *program)
{
    utarray_new(program->data, &char_icd);
}

void
init_utarray_program_intermediate(program_t *program)
{
    utarray_new(program->data, &uint8_t_icd);
}
