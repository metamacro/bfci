#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <bfci/bfci.h>
#include <bfci/data.h>

bfci_status_t
build_program_brackets_hashmap(program_t *program);

bfci_status_t
compile_intermediate(program_t *program);

#endif /* INTERMEDIATE_H */
