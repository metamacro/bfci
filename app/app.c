#include <bfci/bfci.h>
#include <bfci/io.h>
#include <bfci/utils.h>

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, const char *argv[])
{
    int rc = EXIT_SUCCESS;

    program_t program = {0};

    RC_GOTO_IF_NEQ(SUCCESS,
                   bfci_init_program(&program, argc, argv),
                   error);

    /* TODO: compile intermediate code, run */

    goto out;
error:
    rc = EXIT_FAILURE;
out:
    bfci_free_program(&program);

    return rc;
}
