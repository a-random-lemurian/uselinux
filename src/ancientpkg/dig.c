#include "ancientpkg.h"
#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_dig(int argc, char **argv)
{
    int archaeologists = -1;
    int expected_packages = -1;
    int passes = -1;
    int verbose = 0;
    char *jsonfile = NULL;
    char *location = NULL;

    /* TODO: implement these options
    int aggressive_diggers = 0;
    int better_pickaxes;
    int dust_carefully;
    int source_packages;
    int no_proprietary_packages;
    int virus_check;
    int curse_check; */

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
        OPT_STRING(0, "from-json", &jsonfile,
                   "Read package dig config from JSON file"),
        OPT_BOOLEAN('v', "verbose", &verbose, "Verbose output"),
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

        /* TODO: Implement these options
        OPT_BOOLEAN(0, "dust-carefully", &dust_carefully,
                    "Dust for packages more carefully."),
        OPT_BOOLEAN(0, "source-packages", &source_packages,
                    "Include source packages."),
        OPT_BOOLEAN(0, "no-proprietary-packages", &no_proprietary_packages,
                    "Include only free software."), */
        OPT_END()};
    argparse_init(&ap, opts, NULL, 0);
    argparse_parse(&ap, argc, (const char **)argv);

    if (jsonfile != NULL)
    {
        dig_from_json(jsonfile);
    }

    if (has_missing_args(location, archaeologists, passes, expected_packages))
    {
        printf("From the command line: missing arguments.\n");
        exit(1);
    }

    printf("Sending %d archaeologists to %s...\n", archaeologists, location);

    int packages = dig_common(archaeologists, expected_packages, verbose,
                              passes, location, &dcf);

    printf("Found %d packages.\n", packages);
}
