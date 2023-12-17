#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "curse.h"
#include "status.h"
#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <time.h>

void virus_check(DigControlFlags *dcf)
{
    if (!(randint(1, 100000) > 95200))
    {
        return;
    }
    printf("\n" WARN "Malware detected in package. Initializing "
           "virus removal procedure....\n");

    int times = randint(30, 70);
    for (int i = 0; i < times; i++)
    {
        printf("Removing malware... (attempt %d)", i);
        ancientpkg_msleep((randint(54, 134)));

        if (i != times)
        {
            printf("\n");
        }
    }
}

int dust_carefully()
{
    int slp = randint(30, 140);
    ancientpkg_msleep(slp);

    return slp;
}

int purge_proprietary_package(DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "proprietary package detected. searching for free/libre "
                "alternative...\n");

    find_alternative_sources_for_shards(dcf);

    dst->proprietary_packages_purged++;
}

void deal_with_broken_package_shard(DigControlFlags *dcf, int i, char *pkgname)
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

        ancientpkg_msleep(randint(1, 300));

        if (randint(1, 100) > randint(60, 85))
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

static void add_packages_based_on_flags(DigControlFlags *dcf,
                                        DigStatistics *dst)
{
    if (dcf->aggressive_diggers && (randint(1, 1000) > 980))
    {
        dst->packages += randint(4, 20);
    }

    if (dcf->better_pickaxes && (randint(1, 1000) > 980))
    {
        dst->packages += randint(11, 45);
        dst->packages +=
            (dcf->aggressive_diggers && (randint(1, 10000)) > 9780)
                ? randint(53, 90)
                : 0;
    }
}

static void package_extraction_checks(DigControlFlags *dcf, DigStatistics *dst,
                                      int loops)
{
    if (dcf->curse_check)
    {
        curse_check(loops, dst, dcf);
    }
    if (dcf->virus_check)
    {
        virus_check(dcf);
    }
}

static void package_shard_checks(DigControlFlags *dcf, DigStatistics *dst,
                                 int i, int has_missing_shard,
                                 int broken_package_shard)
{
    char pkgname[512];
    sprintf(pkgname, "package-ancient:%d", i);
    if (has_missing_shard && dcf->ignore_missing_shards == 0)
    {
        package_shard_failure(dcf, i, (char *)pkgname);
        dst->missing_shards++;
    }
    else if (broken_package_shard && dcf->ignore_broken_shards == 0)
    {
        deal_with_broken_package_shard(dcf, i, (char *)pkgname);
        dst->broken_shards++;
    }
}

int extract_packages(char *location, int n, int loops, char endch, MTRand mtw,
                     DigControlFlags *dcf, DigStatistics *dst)
{
    int has_missing_shard;
    int dc_slp = 0;
    int broken_package_shard = 0;
    int broken_shard_chance = dcf->aggressive_diggers ? 8600 : 3600;
    long total_time = 0;
    char *src;

    ancientpkg_set_dry_run(dcf->dry_run);

    loops += randint(1, 10);
    for (int i = 0; i < loops; i++)
    {
        total_time = 0;
        int sleep = 0;

        total_time +=
            (dcf->dust_carefully && !dcf->dry_run) ? dust_carefully() : 0;

        if (!dcf->dry_run)
        {
            int sleep = ((int)ceil(gen_rand(&mtw) * 5) + 10);
            total_time += sleep;
        }
        ancientpkg_msleep(sleep);

        broken_package_shard = 0;
        has_missing_shard = 0;
        int status_number =
            generate_status(broken_shard_chance, dcf, &has_missing_shard,
                            &broken_package_shard);
        char *status = status_string(status_number);
        src = dcf->source_packages ? "/src" : "";
        printf("Get:%d:s%d.digsites.site-3/site/%s%s (%ld ms) %s\n", i, n, src,
               location, total_time, status);
        fflush(stdout);
        if (dcf->source_packages)
        {
            dst->source_packages++;
        }
        free(status);

        package_shard_checks(dcf, dst, i, has_missing_shard,
                             broken_package_shard);

        dst->packages++;

        if (dcf->no_proprietary_packages && (randint(1, 1000) > 960))
        {
            purge_proprietary_package(dcf, dst);
        }

        add_packages_based_on_flags(dcf, dst);
        package_extraction_checks(dcf, dst, loops);
    }
    return dst->packages;
}

/**
 * @brief Use the bracket strategy of computing package counts.
 *
 * gaop_factor_brackets() computes the value of out given int a, and int
 * factor. The program takes 10,000 from `a`, which becomes `a1`. Value
 * `c` is generated with the value of `a1` multiplied by the factor, then
 * value `c` is subtracted by value `d`, then incremented to the output
 * value. Value `d` is the bracket tier, multiplied by 50 and
 * then divided by 2.
 *
 * This function very crudely attempts to approximate the principle of
 * diminishing returns. As you add more "archaeologists" to this program
 * to dig up packages, the added productivity bonus you receive should
 * decrease.
 *
 * @param a Archaeologists
 * @param factor Factor to use when multiplying
 * @return int The number of packages
 */
static int gaop_factor_brackets(int a, int factor)
{
    int bt = 1;     /* bt:  Bracket tier            */
    int bs = 10000; /* bs:  Bracket size            */
    int bd = 100;   /* bd:  Bracket decrement       */
    int mbs = 2000; /* mbs: Minimum bracket size    */
    int r_a = a;    /* Remaining a                  */
    int out = 0;    /* Output                       */

    while (r_a != 0)
    {
        if (r_a < bs)
        {
            out += r_a * factor - (int)ceil((bt * 50) / 2);
            r_a = 0;
        }
        else
        {
            out += bs * factor - (int)ceil((bt * 50) / 2);
            r_a -= bs;
        }
        if (bs >= mbs)
        {
            bs -= bd;
            bt++;
        }
    }

    return out;
}

static int generate_amount_of_packages(int a, int factor)
{
    return gaop_factor_brackets(a, factor);
}

int dig_common(int archaeologists, int expected_packages, int passes,
               char *location, DigControlFlags *dcf, DigStatistics *dst)
{
    int loops = generate_amount_of_packages(archaeologists, randint(8, 12));

    if (dcf->source_packages)
    {
        loops += (int)ceil(loops * 0.76);
    }

    MTRand mtw = seed_rand(clock());

    int packages = 0;
    char endch = '\n';

    for (int n = 0; n < passes; n++)
    {
        packages += extract_packages(location, n, loops, endch, mtw, dcf, dst);
    }

    printf("\n");
    return packages;
}

/*
 * Check the archaeologists, passes, location, and expected_packages variables
 * and ensure that they are valid.
 */
int has_missing_args(DigControlFlags *dcf, char *location, int archaeologists,
                     int passes, int expected_packages)
{
    int had_fatal_err = 0;
    if (location == NULL)
    {
        printf(ERROR "location must be specified\n");
        had_fatal_err = 1;
    }

    if (!dcf->force_archaeologists)
    {
        if (archaeologists <= 1)
        {
            printf(ERROR "need more than 1 archaeologist.\n");
            had_fatal_err = 1;
        }

        if (archaeologists > 8000000000)
        {
            printf(ERROR
                   "Too many archaeologists (not everyone in the world is "
                   "one,)\n");
            had_fatal_err = 1;
        }
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

/*
 * Set the dig control flags to their default values. Always call this method
 * when preparing a DigControlFlags struct to prevent undefined values and
 * behavior.
 */
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

/*
 * Notify the user that there was a failure in retrieving a package shard.
 */
void package_shard_failure(DigControlFlags *dcf, int i, char *pkgname)
{
    printf(WARN "failed to get package shard %d %s (stable)\n", i, pkgname);
    printf("attempting to resolve the situation....\n");
    ancientpkg_msleep(randint(100, 3000));
    find_alternative_sources_for_shards(dcf);
}
