#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>
#include <stdio.h>

/* clang-format off */
#ifdef DEBUG
    #define TRACE_ON 1
#else
    #define TRACE_ON 0
#endif
/* clang-format on */

#define STRINGIFY(X)  #X
/* expand first then stringify */
#define ESTRINGIFY(X) STRINGIFY(X)

#define TRACE(F, X)                                                               \
    do {                                                                          \
        if (TRACE_ON)                                                             \
            fprintf(stderr,                                                       \
                    "%s:%s:" ESTRINGIFY(__LINE__) ":(" STRINGIFY(X) "): " F "\n", \
                    __FILE__,                                                     \
                    __func__,                                                     \
                    (X));                                                         \
    } while (false)

#endif /* DEBUG_H */
