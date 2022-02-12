#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR BHRED "error: " reset

int cmd_dig(int argc, char **argv)
{
    int archaeologists = -1;
    int expected_packages = -1;
    int passes = -1;
    int verbose = 0;
    char *location = NULL;

    /* TODO: implement these options
    int aggressive_diggers = 0;
    int better_pickaxes;
    int dust_carefully;
    int source_packages;
    int no_proprietary_packages;
    int virus_check;
    int curse_check; */

    struct argparse ap;
    struct argparse_option opts[] = {
        OPT_HELP(),
        OPT_INTEGER('a', "archaeologists", &archaeologists,
                    "Archaeologists to send."),
        OPT_INTEGER('p', "expected-pkgs", &expected_packages,
                    "Packages to expect from digging job."),
        OPT_INTEGER('P', "passes", &passes, "Number of passes to make."),
        OPT_STRING('l', "location", &location, "Location of package dig job."),
        OPT_BOOLEAN('v', "version", &verbose, "Verbose output"),

        /* TODO: Implement these options
        OPT_BOOLEAN(0, "aggressive-diggers", &aggressive_diggers,
                    "Dig very aggressively."),
        OPT_BOOLEAN(0, "better-pickaxes", &better_pickaxes,
                    "Provide diggers with better pickaxes."),
        OPT_BOOLEAN(0, "dust-carefully", &dust_carefully,
                    "Dust for packages more carefully."),
        OPT_BOOLEAN(0, "source-packages", &source_packages,
                    "Include source packages."),
        OPT_BOOLEAN(0, "no-proprietary-packages", &no_proprietary_packages,
                    "Include only free software."),
        OPT_BOOLEAN(0, "virus-check", &virus_check,
                    "Scan packages for viruses."),
        OPT_BOOLEAN(0, "curse-check", &curse_check,
                    "Scan packages for ancient curses."), */
        OPT_END()};
    argparse_init(&ap, opts, NULL, 0);
    argparse_parse(&ap, argc, (const char **)argv);

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
        exit(1);
    }

    printf("Sending %d archaeologists to %s...\n", archaeologists, location);

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

    printf("Found %d packages.\n", packages);
}
