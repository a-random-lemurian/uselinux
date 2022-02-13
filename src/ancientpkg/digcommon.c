#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <time.h>
#include <stdio.h>

int dig_common(int archaeologists, int expected_packages,
               int verbose, int passes, char* location)
{
    int loops = (int)ceil((archaeologists * 10) + expected_packages);

    MTRand mtw = seedRand(clock());

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

    return had_fatal_err;
}

int set_dig_control_flags(DigControlFlags* dcf, int aggressive_diggers, int better_pickaxes,
                          int dust_carefully, int source_packages,
                          int no_proprietary_packages, int virus_check,
                          int curse_check)
{
    dcf->aggressive_diggers = aggressive_diggers;
    dcf->better_pickaxes = better_pickaxes;
    dcf->dust_carefully = dust_carefully;
    dcf->source_packages = source_packages;
    dcf->no_proprietary_packages = no_proprietary_packages;
    dcf->virus_check = virus_check;
    dcf->curse_check = curse_check;
    return 0;
}
