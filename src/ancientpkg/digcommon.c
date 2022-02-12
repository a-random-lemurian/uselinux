#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <stdio.h>

int has_missing_args(char* location, int archaeologists,
               int passes, int expected_packages)
{
    int had_fatal_err = 0;
    if (location == NULL)
    {
        printf(ERROR "location must be specified\n");
        had_fatal_err = 1;
    }
    if (archaeologists <= 1)
    {
        printf(ERROR "need more than 1 archaeologist.\n");
        had_fatal_err = 1;
    }
    if (passes <= 0)
    {
        printf(ERROR "need more than 1 pass.\n");
        had_fatal_err = 1;
    }
    if (expected_packages <= 0)
    {
        printf(ERROR "need to expect more than 1 package.\n");
        had_fatal_err = 1;
    }
    if (had_fatal_err)
    {
        printf("use --help for help.\n");
        return 1;
    }
}
