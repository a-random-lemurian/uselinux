#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <time.h>

int dig_common(int archaeologists, int expected_packages, int verbose,
               int passes, char *location, DigControlFlags* dcf)
{
    int loops = (int)ceil((archaeologists * 10) + expected_packages);

    MTRand mtw = seedRand(clock());

    int packages = 0;
    char endch = verbose ? '\n' : '\r';

    for (int n = 0; n < passes; n++)
    {
        for (int i = 0; i < ((loops) + randint(1, 10)); i++)
        {
            int sleep = ((int)ceil(genRand(&mtw) * 5) + 10);
            msleep(sleep);

            printf("Get:%d:s%d.digsites.site-3/site/%s (%d ms) ", i, n,
                   location, sleep);
            fflush(stdout);
            if ((randint(1, 10000)) > 9995)
            {
                printf(" [404 Not Found]");
                printf("\n");
                char pkgname[512];
                sprintf(pkgname, "package-ancient:%d", i);
                package_shard_failure(i, (char *)pkgname);
            }
            else
            {
                printf("[200 OK]");
            }
            if (verbose)
            {
                printf(" (clock: %ld ms)", clock());
            }
            printf("                            %c", endch);
            packages++;
            if (dcf->virus_check)
            {
                if ((randint(1,100000) > 95200))
                {
                    printf(WARN "Malware detected in package. Initializing "
                           "virus removal procedure....\n");

                    for (int i = 0; i < (randint(30, 70)); i++)
                    {
                        printf("Removing malware...\n");
                        msleep((randint(54, 134)));
                    }
                }
            }
        }

        if (!verbose)
        {
            printf("\n");
        }
    }

    printf("\n");
    return packages;
}

int has_missing_args(char *location, int archaeologists, int passes,
                     int expected_packages)
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

int set_dig_control_flags(DigControlFlags *dcf, int aggressive_diggers,
                          int better_pickaxes, int dust_carefully,
                          int source_packages, int no_proprietary_packages,
                          int virus_check, int curse_check)
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

int set_default_dig_control_flags(DigControlFlags *dcf)
{
    dcf->aggressive_diggers = 0;
    dcf->better_pickaxes = 0;
    dcf->dust_carefully = 0;
    dcf->source_packages = 0;
    dcf->no_proprietary_packages = 0;
    dcf->virus_check = 0;
    dcf->curse_check = 0;
    return 0;
}

void package_shard_failure(int i, char *pkgname)
{
    printf(WARN "failed to get package shard %d %s (stable)\n", i, pkgname);

    printf("attempting to resolve the situation....\n");
    msleep(randint(100, 3000));
    for (int n = 0; n < 400; n++)
    {
        printf("Checking package src %d.... ", n);
        fflush(stdout);
        msleep(randint(1, 300));
        if (randint(1, 100) > 90)
        {
            printf("shard found.\n");
            break;
        }
        else
        {
            printf(" shard not found.\n");
        }
    }
}
