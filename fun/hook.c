#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include "enable_hook.h"

typedef int (*orig_open_f_type)(const char *pathname, int flags);

int open(const char *pathname, int flags, ...) {
    orig_open_f_type orig_open;
    orig_open = (orig_open_f_type)dlsym(RTLD_NEXT, "open");
    printf("Opening file %s with flags %d\n", pathname, flags);
    return orig_open(pathname, flags);
}

int enable_hook()
{
    return 1;
}