#include "ancientpkg.h"
#include <stdio.h>
#include <time.h>

void print_dig_stats_report(DigStatistics *dst, DigControlFlags *dcf)
{
    if (dcf->no_stats)
    {
        return;
    }

    printf("Packages:\n");
    if (dcf->ignore_broken_shards == 0)
    {
        printf("    Broken shards:  %d\n", dst->broken_shards);
    }

    if (dcf->ignore_missing_shards == 0)
    {
        printf("    Missing shards: %d\n", dst->missing_shards);
    }
    printf("    Usable shards:  %d\n",
           (dst->packages - (dst->broken_shards + dst->missing_shards)));

    printf("    Total:          %d\n", dst->packages);

    if (dcf->no_proprietary_packages)
    {
        printf("Proprietary packages purged and removed: %d\n",
               dst->proprietary_packages_purged);
    }

    if (dcf->curse_check && !dcf->show_all_stats)
    {
        printf("Cursed packages: %d\n", dst->cursed_packages);
        printf("Cleansing rituals performed: %d\n",
               dst->cleansing_rituals_performed);
        printf("Total salt used in kilograms: %Lf\n", dst->salt_used_kg);
    }

    if (dcf->source_packages && !dcf->show_all_stats)
    {
        printf("Total source packages: %d\n", dst->source_packages);
    }
}

void initialize_dig_stats(DigStatistics *dst)
{
    dst->broken_shards = 0;
    dst->missing_shards = 0;
    dst->packages = 0;
    dst->cleansing_rituals_performed = 0;
    dst->cursed_packages = 0;
    dst->salt_used_kg = 0;
    dst->source_packages = 0;
}
