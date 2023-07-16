#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define UNUSED(X) (void)(X)

#define RC_GOTO_IF_EQ(CMP, FUNC, LABEL) \
    do {                                \
        if ((CMP) == (FUNC))            \
            goto LABEL;                 \
    } while (false)

#define RC_GOTO_IF_NEQ(CMP, FUNC, LABEL) \
    do {                                 \
        if ((CMP) != (FUNC))             \
            goto LABEL;                  \
    } while (false)

#define RUN_IF_NON_NULL(PTR, FUNC) \
    do {                           \
        if (XNULL != (PTR))        \
            FUNC;                  \
    } while (false)

#endif /* UTILS_H */
