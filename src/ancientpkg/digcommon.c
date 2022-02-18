#include <ancientpkg.h>
#include "cursedpkg.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <time.h>

static PackageCurse curses[] = {
    {"disease", "Diseased package", cmit_diseased_pkg},
    {"memetic", "Infohazardous package", cmit_infohazard}
};

int mitigate_curse(DigStatistics *dst, DigControlFlags *dcf)
{
    MTRand mtw = seedRand(clock());

    curses[(int)floor(genRand(&mtw) * (sizeof(curses)/sizeof(curses[0])))]
         .fn(0, dcf, dst);
}

int curse_check(int loops, DigStatistics *dst, DigControlFlags *dcf)
{

    int i = 0;

    if ((randint(1, 100000)) > 91700)
    {
        dst->cursed_packages++;

        printf("\n" WARN "curse detected in package.");
        repeat(' ', 30);
        printf("\n");

        if (!dcf->dry_run)
        {
            msleep((randint(35, 88)));
        }

        int n = randint(1, 1000);

        printf(WARN "digsite %d lockdown initiated.\n", loops);

        mitigate_curse(dst, dcf);
    }

    return i;
}

void virus_check(DigControlFlags* dcf)
{
    if ((randint(1, 100000) > 95200))
    {
        printf("\n" WARN "Malware detected in package. Initializing "
               "virus removal procedure....\n");

        int times = randint(30, 70);
        for (int i = 0; i < times; i++)
        {
            printf("Removing malware... (attempt %d)", i);

            if (!dcf->dry_run)
            {
                msleep((randint(54, 134)));
            }

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

int purge_proprietary_package(DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "proprietary package detected. searching for free/libre "
                "alternative...\n");

    find_alternative_sources_for_shards(dcf);

    dst->proprietary_packages_purged++;
}

void deal_with_broken_package_shard(DigControlFlags* dcf, int i, char* pkgname)
{
    printf(WARN "Package shard %i of %s is broken!\n", i, pkgname);
    printf("Looking for alternative sources...\n");
    find_alternative_sources_for_shards(dcf);
}

void find_alternative_sources_for_shards(DigControlFlags *dcf)
{
    for (int n = 0; n < 400; n++)
    {
        printf("Checking package src %d.... ", n);
        fflush(stdout);

        if (!dcf->dry_run)
        {
            msleep(randint(1, 300));
        }

        if (randint(1, 100) > 90)
        {
            printf("shard " BHGRN "found." reset "\n");
            break;
        }
        else
        {
            printf("shard " BHRED "not found." reset "\n");
        }
    }
}

int extract_packages(char *location, int n,
                     int loops, char endch, MTRand mtw, DigControlFlags *dcf,
                     DigStatistics* dst)
{
    int pkgs = 0;
    char* status;
    int has_missing_shard;
    int dc_slp = 0;
    int broken_package_shard = 0;
    int broken_shard_chance = 8600;

    if (dcf->aggressive_diggers)
    {
        broken_shard_chance -= 5000;
    }

    for (int i = 0; i < loops + randint(1, 10); i++)
    {
        clock_t t1_before = clock();

        if (dcf->dust_carefully && !dcf->dry_run)
        {
            dc_slp = dust_carefully();
        }

        int sleep = 0;
        if (!dcf->dry_run)
        {
            int sleep = ((int)ceil(genRand(&mtw) * 5) + 10);
            msleep(sleep);
        }

        broken_package_shard = 0;
        has_missing_shard = 0;

        status = "[200 OK]";
        
        int rand = randint(1, 10000);
        if (rand > 9775)
        {
            has_missing_shard = 1;
            status = "[404 Not Found]";
        }
        else if (rand > broken_shard_chance && dcf->ignore_broken_shards == 0)
        {
            broken_package_shard = 1;
            status = "[500 Internal Server Error]";
        }
        else
        {
            if (!dcf->dry_run)
            {
                msleep(1);
            }
        }


        printf("Get:%d:s%d.digsites.site-3/site/%s (%d ms) %s\n",
               i, n, location, (sleep + dc_slp), status);
        fflush(stdout);

        if (dcf->source_packages)
        {
            printf("Get:%d:s%d.digsites.site-3/site/src/%s (%d ms) %s "
                   "<SOURCE>\n",
                   i, n, location, (sleep + dc_slp), status);
            fflush(stdout);
            dst->source_packages++;
            dst->packages++;
        }

        if (has_missing_shard && dcf->ignore_missing_shards == 0)
        {
            char pkgname[512];
            sprintf(pkgname, "package-ancient:%d", i);
            package_shard_failure(dcf, i, (char *)pkgname);

            dst->missing_shards++;
        }
        else if (broken_package_shard && dcf->ignore_broken_shards == 0)
        {
            char pkgname[512];
            sprintf(pkgname, "package-ancient:%d", i);
            deal_with_broken_package_shard(dcf, i, (char *)pkgname);
        
            dst->broken_shards++;
        }

        pkgs++;

        if (dcf->no_proprietary_packages)
        {
            if ((randint(1, 1000) > 960))
            {
                purge_proprietary_package(dcf, dst);
            }
        }

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
            curse_check(loops, dst, dcf);
        }

        if (dcf->virus_check)
        {
            virus_check(dcf);
        }
    }

    dst->packages += pkgs;
    return pkgs;
}

int validate_archaeologists(int archaeologists)
{
    int had_fatal_err;
    int rc;

    if (archaeologists > 7000000000)
    {
        printf(ERROR "Too many archaeologists (not everyone in the world is "
                                              "one,)\n");
        rc = 1;
    }

    if (had_fatal_err)
    {
        exit(rc);
    }
}

int dig_common(int archaeologists, int expected_packages, int verbose,
               int passes, char *location, DigControlFlags *dcf,
               DigStatistics* dst)
{
    validate_archaeologists(archaeologists);

    int loops = (int)ceil((archaeologists * 10) + expected_packages);

    if (dcf->source_packages)
    {
        loops += (int)ceil(loops * 0.76);
    }

    MTRand mtw = seedRand(clock());

    int packages = 0;
    char endch = '\n';

    for (int n = 0; n < passes; n++)
    {
        packages += extract_packages(location, n, loops, endch, mtw, dcf, dst);
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
    dcf->dry_run = 0;
    dcf->show_all_stats = 0;
    dcf->no_stats = 0;
    return 0;
}

void package_shard_failure(DigControlFlags* dcf, int i, char *pkgname)
{
    printf(WARN "failed to get package shard %d %s (stable)\n", i, pkgname);

    printf("attempting to resolve the situation....\n");

    if (!dcf->dry_run)
    {
        msleep(randint(100, 3000));
    }

    find_alternative_sources_for_shards(dcf);
}
