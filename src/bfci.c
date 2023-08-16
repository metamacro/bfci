#include <bfci/bfci.h>
#include <bfci/data.h>
#include <bfci/debug.h>
#include <bfci/intermediate.h>
#include <bfci/io.h>
#include <bfci/utils.h>

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
