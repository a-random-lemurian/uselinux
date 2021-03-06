#include <common/argparse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rmbloatapi.h"

static int fast_flag = 0;

static const char *const usage[] = {"rmbloat-rm [PACKAGES]",
                                    "rmbloat-rm --help",
                                    "rmbloat-rm --fast [PACKAGES]\n", NULL};

int rmbloat_rm(int argc, char **argv)
{
    int list = 0;
    int fast = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_BOOLEAN('l', "list", &list,
                    "Does nothing, preserved for "
                    "backwards compatibility"),
        OPT_BOOLEAN(0, "fast", &fast, "Remove bloat faster"), OPT_END()};

    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, "Remove bloat from the command line", "\n");
    argc = argparse_parse(&argparse, argc, (const char **)argv);

    for (int i = 1; i < argc; i++)
    {
        remove_bloatware(argv[i], fast);
    }
}