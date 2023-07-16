#include <bfci/bfci.h>
#include <bfci/debug.h>
#include <bfci/io.h>
#include <bfci/memory.h>
#include <bfci/utils.h>

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, const char *argv[])
{
    int rc = EXIT_SUCCESS;

    program_t program = {0};

    RC_GOTO_IF_NEQ(SUCCESS,
                   argparse(argc, argv, &program),
                   error);

    RC_GOTO_IF_NEQ(SUCCESS,
                   read_program(&program),
                   error);

    print_program(&program);

    goto out;
error:
    rc = EXIT_FAILURE;
out:
    free_program(&program);

    return rc;
}
