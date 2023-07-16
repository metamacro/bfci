#ifndef IO_H
#define IO_H

#include <bfci/bfci.h>

bfci_status_t
argparse(int argc, const char *argv[], program_t *program);

bfci_status_t
read_program(program_t *program);

void
print_program(program_t *program);

#endif /* IO_H */
