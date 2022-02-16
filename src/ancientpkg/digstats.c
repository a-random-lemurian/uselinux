#include "ancientpkg.h"
#include <stdio.h>
#include <time.h>


void print_dig_stats_report(DigStatistics *dst)
{
    /* TODO: only show statistics relevant to flags passed for job */
    printf("Broken package shards: %d\n", dst->broken_shards);
    printf("Missing package shards: %d\n", dst->missing_shards);
    printf("Total packages found: %d\n", dst->packages);
    printf("Cursed packages: %d\n", dst->cursed_packages);
    printf("Cleansing rituals performed: %d\n",
           dst->cleansing_rituals_performed);
    printf("Total salt used in kilograms: %Lf\n", dst->salt_used_kg);
    printf("Total source packages: %d\n", dst->source_packages);
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
