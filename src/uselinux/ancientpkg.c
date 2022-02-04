#include <math.h>
#include <stdio.h>
#include <time.h>

#include "ancientpkg.h"
#include "mtwister.h"
#include "utils.h"

int pkg_dig_job_sanity_check(pkg_dig_job *job)
{
    if (job->dig_coverage >= 1 && job->dig_coverage <= 10)
    {
        return 1;
    }

    return 0;
}

int mk_pdj_safe(char *location, int dig_coverage, pkg_dig_job *job)
{
    job->dig_coverage = dig_coverage;
    job->location = location;

    if (pkg_dig_job_sanity_check(job) != 0)
    {
        return 1;
    };

    return 0;
};

void pdjctl_set_defaults(pkg_dig_job_control *ctl)
{
    ctl->max_locs = -1;
    ctl->max_sites = -1;
}

void package_dig_job(pkg_dig_job *job, int sanity, pkg_dig_job_control *ctl)
{
    if (sanity)
    {
        pkg_dig_job_sanity_check(job);
    }

    int archaeologists = 10 + (job->dig_coverage * 3 / 2) + randint(2, 5);

    printf("Sending %d archaeologists to %s.\n", archaeologists,
           job->location);

    msleep(randint(100, 4000));

    int sites = archaeologists * 3 + (job->dig_coverage * 2) + randint(3, 9);

    if (sites >= ctl->max_sites)
    {
        sites = ctl->max_sites;
    }

    int totalpackages = 0;
    int totalsleep = 0;

    for (int i = 0; i < sites; i++)
    {
        int packages = randint(10, 40) * (job->dig_coverage / 4);

        int sleep = randint(300, 5000);
        totalsleep += sleep;
        totalpackages += packages;

        msleep(sleep);

        printf("Site %d of %d, found %d packages in %d ms.\n", i + 1, sites,
               packages, sleep);

        if (i >= ctl->max_sites - 1 && ctl->max_sites != 1)
        {
            break;
        }
    }

    long double packs_per_sec = totalsleep / totalpackages;
    printf("Found %d packages in %d ms (%Lf pkgs / sec)\n", totalpackages,
           totalsleep, packs_per_sec);
}

void ancient_debian_packages_v2(pkg_dig_job_control *ctl)
{
    char locations[][127] = {"Egypt", "Ancient APT Servers"};

    int locs;
    if (ctl->max_locs != -1 && ctl->max_locs <= LEN(locations))
    {
        locs = ctl->max_locs;
    }
    else
    {
        locs = LEN(locations);
    }

    for (int i = 0; i < locs; i++)
    {

        pkg_dig_job job;
        mk_pdj_safe(locations[i], 8, &job);

        printf("Location %d of %d.\n", i + 1, locs);
        package_dig_job(&job, 1, ctl);
    }
}

int check_digsite(int i)
{
    printf("-------- [Digsite %d] --------\n", i);
    printf("Digging for packages.... ");
    fflush(stdout);
    int packages = randint(300, 800);
    printf("found %d\n", packages);

    return packages;
}

void ancient_debian_packages()
{
    int digsites = randint(300, 900);

    printf("Travelling to digsites to find ancient Debian packages.\n");

    int total_packages = 0;

    for (int i = 0; i < digsites; i++)
    {
        total_packages += check_digsite(i);
    }

    printf("Finished digging.... found %d total packages.", total_packages);
}
