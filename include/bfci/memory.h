#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* jens gustedt got me */
#define XNULL (void *)0

#define XFREE(X)     \
    do {             \
        free(X);     \
        (X) = XNULL; \
    } while (false)

void *
xmalloc(size_t sz);

#endif /* MEMORY_H */
