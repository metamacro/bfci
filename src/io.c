#include <bfci/bfci.h>
#include <bfci/data.h>
#include <bfci/debug.h>
#include <bfci/io.h>
#include <bfci/memory.h>
#include <bfci/utils.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static inline void
print_help(void)
{
    fprintf(stderr,
#include "help.txt"
    );
}

static inline void
copy_program_path(const char *srcpath, program_t *program)
{
    size_t progpath_sz = 0;

    progpath_sz       = sizeof(char) * (strlen(srcpath) + 1);
    program->progpath = xmalloc(progpath_sz);

    strncpy(program->progpath, srcpath, progpath_sz);
}

bfci_status_t
argparse(int argc, const char *argv[], program_t *program)
{
    int rc = SUCCESS;

    if (argc != 2) {
        print_help();
        rc = FAILURE;
    } else {
        copy_program_path(argv[1], program);
        TRACE("%s", program->progpath);
    }

    TRACE("%d", rc);
    return rc;
}

static inline bool
file_exists(const char *fpath)
{
    return 0 == access(fpath, F_OK);
}

static inline bool
is_valid_character(char c)
{
    if (c == CMD_PLUS
        || c == CMD_MINUS
        || c == CMD_LT
        || c == CMD_GT
        || c == CMD_DOT
        || c == CMD_COMMA
        || c == CMD_SB_OPEN
        || c == CMD_SB_CLOSED) return true;

    if (isprint(c)) TRACE("invalid character: '%c'", c);
    else TRACE("invalid character: '0x%02hhX'", c);
    return false;
}

bfci_status_t
read_program(program_t *program)
{
    int   rc = SUCCESS;
    int   c  = 0;
    FILE *fp = XNULL;

    RC_GOTO_IF_NEQ(true, file_exists(program->progpath), error);

    fp = fopen(program->progpath, "r");

    init_utarray_program_instructions(program);

    while (EOF != (c = fgetc(fp)))
        if (is_valid_character((char)c))
            utarray_push_back(program->instructions, &c);

    goto out;
error:
    rc = FAILURE;
out:
    RUN_IF_NON_NULL(fp, fclose(fp));
    TRACE("%d", rc);
    return rc;
}

void
print_program(program_t *program)
{
    char *cp = XNULL;

    UT_ARRAY_ITER(program->instructions, cp, char *)
    {
        putchar(*cp);
    }
}
