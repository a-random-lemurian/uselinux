#include "ancientpkg.h"
#include <stdio.h>
#include <time.h>


void print_dig_stats_report(DigStatistics *dst)
{
    printf("Broken package shards: %d\n"
           "Missing package shards: %d\n"
           "Total packages found: %d\n",
           
           dst->broken_shards,
           dst->missing_shards,
           dst->packages);
}

void initialize_dig_stats(DigStatistics *dst)
{
    dst->broken_shards = 0;
    dst->missing_shards = 0;
    dst->packages = 0;
}
