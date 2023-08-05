#include <bfci/data.h>

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
    utarray_new(program->instructions, &uint8_t_icd);
}

void
free_utarray_program_intermediate(program_t *program)
{
    utarray_free(program->intermediate);
}
