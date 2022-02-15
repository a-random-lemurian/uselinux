#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <time.h>

void perform_ritual(int i, int *ritual_success)
{
    printf("%ld:attempting cleansing ritual... attempt %d", clock(), i);

    if ((randint(1, 1000)) > 230)
    {
        printf(", " BHRED "failed." reset "\n");
    }
    else
    {
        printf(", " BHGRN "success.\n" reset);
        *ritual_success = 1;
    }

    msleep((randint(244, 652)));
}

void curse_check(int loops)
{
    if ((randint(1, 100000)) > 91700)
    {
        printf("\n" WARN "curse detected in package.");
        repeat(' ', 30);
        printf("\n");
        msleep((randint(35, 88)));

        int n = randint(1, 1000);

        printf(WARN "digsite %d lockdown initiated.\n", loops);
        int ritual_success = 0;
        int i = 0;
        while (ritual_success == 0)
        {
            perform_ritual(i, &ritual_success);
            i++;
        }
    }
}

void virus_check()
{
    if ((randint(1, 100000) > 95200))
    {
        printf("\n" WARN "Malware detected in package. Initializing "
               "virus removal procedure....\n");

        int times = randint(30, 70);
        for (int i = 0; i < times; i++)
        {
            printf("Removing malware... (attempt %d)", i);
            msleep((randint(54, 134)));

            if (i != times)
            {
                printf("\n");
            }
        }
    }
}

int dust_carefully()
{
    int slp = randint(30, 140);
    msleep(slp);

    return slp;
}

void deal_with_broken_package_shard(int i, char* pkgname)
{
    printf(WARN "Package shard %i of %s is broken!\n", i, pkgname);
    printf("Looking for alternative sources...\n");
    find_alternative_sources_for_shards();
}

void find_alternative_sources_for_shards()
{
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

int extract_packages(char *location, int n, int verbose, int *packages,
                     int loops, char endch, MTRand mtw, DigControlFlags *dcf)
{
    int pkgs = 0;
    char* status;
    int has_missing_shard;
    int dc_slp = 0;
    int broken_package_shard = 0;

    for (int i = 0; i < ((loops) + randint(1, 10)); i++)
    {
        clock_t t1_before = clock();

        if (dcf->dust_carefully)
        {
            dc_slp = dust_carefully();
        }

        int sleep = ((int)ceil(genRand(&mtw) * 5) + 10);
        msleep(sleep);

        broken_package_shard = 0;
        has_missing_shard = 0;

        status = "[200 OK]";
        
        int rand = randint(1, 10000);
        if (rand > 9775)
        {
            has_missing_shard = 1;
            status = "[404 Not Found]";
        }
        else if (rand > 8600 && dcf->ignore_broken_shards == 0)
        {
            broken_package_shard = 1;
            status = "[500 Internal Server Error]";
        }
        else
        {
            msleep(1);
        }


        printf("Get:%d:s%d.digsites.site-3/site/%s (%d ms) %s\n",
               i, n, location, (sleep + dc_slp), status);
        fflush(stdout);

        if (has_missing_shard && dcf->ignore_missing_shards == 0)
        {
            char pkgname[512];
            sprintf(pkgname, "package-ancient:%d", i);
            package_shard_failure(i, (char *)pkgname);
        }
        else if (broken_package_shard && dcf->ignore_broken_shards == 0)
        {
            char pkgname[512];
            sprintf(pkgname, "package-ancient:%d", i);
            deal_with_broken_package_shard(i, (char *)pkgname);
        }

        pkgs++;


        if (dcf->aggressive_diggers)
        {
            if ((randint(1, 1000) > 980))
            {
                pkgs += randint(4, 20);
            }
        }

        if (dcf->better_pickaxes)
        {
            if ((randint(1, 1000) > 980))
            {
                pkgs += randint(11, 45);

                if (dcf->aggressive_diggers && (randint(1, 10000)) > 9780)
                {
                    pkgs += randint(53, 90);
                }
            }
        }

        if (dcf->curse_check)
        {
            curse_check(loops);
        }

        if (dcf->virus_check)
        {
            virus_check();
        }
    }

    return pkgs;
}

int dig_common(int archaeologists, int expected_packages, int verbose,
               int passes, char *location, DigControlFlags *dcf)
{
    int loops = (int)ceil((archaeologists * 10) + expected_packages);

    MTRand mtw = seedRand(clock());

    int packages = 0;
    char endch = '\n';

    for (int n = 0; n < passes; n++)
    {
        packages += extract_packages(location, n, verbose, &packages, loops,
                                     endch, mtw, dcf);
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
    dcf->ignore_missing_shards = 0;
    dcf->ignore_broken_shards = 0;
    return 0;
}

void package_shard_failure(int i, char *pkgname)
{
    printf(WARN "failed to get package shard %d %s (stable)\n", i, pkgname);

    printf("attempting to resolve the situation....\n");
    msleep(randint(100, 3000));
    find_alternative_sources_for_shards();
}
