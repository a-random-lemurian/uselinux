#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <stdio.h>

int dig_common(int archaeologists, int expected_packages,
               int verbose, int passes, char* location)
{
    int loops = (int)ceil((archaeologists * 10) + expected_packages);

    MTRand mtw = seedRand(((unsigned long)loops + clock()));

    int packages = 0;
    char endch = verbose ? '\n' : '\r';

    for (int n = 0; n < passes; n++)
    {
        for (int i = 0; i < loops; i++)
        {
            int sleep = ((int)ceil(genRand(&mtw) * 5) + 10);
            msleep(sleep);
            printf("Get:%d:s%d.digsites.site-3/site/%s (%d ms) [200 OK]       "
                   "       %c",
                   i, n, location, sleep, endch);
            fflush(stdout);
            packages++;
        }
    }

    return packages;
}

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
