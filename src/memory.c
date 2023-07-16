#include <bfci/memory.h>

void *
xmalloc(size_t sz)
{
    void *p = XNULL;

    p = malloc(sz);

    if (0 == sz
        || XNULL == p) abort();

    return p;
}
