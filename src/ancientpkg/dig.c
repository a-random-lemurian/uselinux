#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "validate_args.h"

int cmd_dig(int argc, char **argv)
{
    int archaeologists = -1;
    int expected_packages = -1;
    int passes = -1;
    int verbose = 0;
    char *jsonfile = NULL;
    char *location = NULL;

    DigControlFlags dcf;
    set_default_dig_control_flags(&dcf);

    struct argparse ap;
    struct argparse_option opts[] = {
        OPT_HELP(),
        OPT_INTEGER('a', "archaeologists", &archaeologists,
                    "Archaeologists to send."),
        OPT_INTEGER('p', "expected-pkgs", &expected_packages,
                    "Packages to expect from digging job."),
        OPT_INTEGER('P', "passes", &passes, "Number of passes to make."),
        OPT_STRING('l', "location", &location, "Location of package dig job."),
        OPT_BOOLEAN('v', "verbose", &verbose, "Verbose output"),
        OPT_BOOLEAN(0, "dry-run", &dcf.dry_run, "Don't wait"),
        OPT_STRING(0, "from-json", &jsonfile,
                   "Read package dig config from JSON file"),
        OPT_BOOLEAN(0, "show-all-stats", &dcf.show_all_stats,
                    "Show all dig statistics"),
        OPT_BOOLEAN(0, "no-stats", &dcf.no_stats,
                    "Don't show any stats at all"),
        OPT_GROUP("Flags that control the package excavation job"),
        OPT_BOOLEAN(0, "virus-check", &dcf.virus_check,
                    "Scan packages for viruses."),
        OPT_BOOLEAN(0, "curse-check", &dcf.curse_check,
                    "Scan packages for ancient curses."),
        OPT_BOOLEAN(0, "aggressive-diggers", &dcf.aggressive_diggers,
                    "Dig very aggressively."),
        OPT_BOOLEAN(0, "better-pickaxes", &dcf.better_pickaxes,
                    "Provide diggers with better pickaxes."),
        OPT_BOOLEAN(0, "ignore-missing-shards", &dcf.ignore_missing_shards,
                    "Ignore missing package shards"),
        OPT_BOOLEAN(0, "ignore-broken-shards", &dcf.ignore_broken_shards,
                    "Ignore physically broken package shards"),
        OPT_BOOLEAN(0, "dust-carefully", &dcf.dust_carefully,
                    "Dust for packages more carefully."),
        OPT_BOOLEAN(0, "source-packages", &dcf.source_packages,
                    "Include source packages."),
        OPT_BOOLEAN(0, "no-proprietary-packages", &dcf.no_proprietary_packages,
                    "Include only free software."),
        OPT_GROUP("Other flags"),
        OPT_BOOLEAN(0, "force-archaeologists", &dcf.force_archaeologists,
                    "Ignore population limit of 8 billion on archaeologists"),
        OPT_END()};

    const char *usages[] = {
        "ancientpkg dig [--help] [--passes=<int>] [--location=<str>] \n"
        "       [--expected-pkgs=<int>] [--archaeologists=<int>] "
        "[<FLAGS>]\n",
        NULL};

    argparse_init(&ap, opts, usages, 0);
    argparse_describe(&ap,
                      "The universal package excavation system "
                      "(Debian has ancient packages, anyway)",
                      /**********************************************/
                      "Packages may contain ancient curses leading to "
                      "injury or death.");
    argparse_parse(&ap, argc, (const char **)argv);

    if (jsonfile != NULL)
    {
        dig_from_json(jsonfile);
    }

    if (validate_arguments(&dcf, location, archaeologists, passes,
                         expected_packages))
    {
        printf("From the command line: missing arguments.\n");
        exit(1);
    }

    dcf.location = location;

    printf("Sending %d archaeologists to %s...\n", archaeologists, location);

    DigStatistics dst;
    initialize_dig_stats(&dst);

    ancientpkg_set_dry_run(dcf.dry_run);

    dig_common(archaeologists, expected_packages, passes, location, &dcf,
               &dst);

    print_dig_stats_report(&dst, &dcf);

    return 0;
}
