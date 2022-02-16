#include "rmbloatapi.h"
#include <stdio.h>

#include <common/argparse.h>
#include <common/utils.h>

int fast;

void print_help()
{
    printf("rmbloat - remove bloated software or any software you don't "
           "like\n\n");
}

static const char *const usage[] = {
    "rmbloat from-file [options] [[--] args]",
    "rmbloat from-file [options]",
    NULL,
};

int rmbloat_from_file(int argc, const char **argv)
{
    if (argc == 1)
    {
        printf("No arguments specified.\n");
        exit(1);
    }

    int wait = 0;
    int fast = 0;
    char *file;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('w', "wait", &wait, "wait 10 seconds before starting"),
        OPT_BOOLEAN('s', "fast", &fast, "remove bloat faster"),
        OPT_STRING('f', "file", &file, "path to file"),
        OPT_END()};

    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argparse_describe(
        &argparse, "\nRemove bloated packages from a list in a file.", "\n-");
    argc = argparse_parse(&argparse, argc, argv);

    FILE *fp = fopen(file, "r");
    char **rm_pkgs;
    char *pkg;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        line[strcspn(pkg, "\r\n")] = 0;
        remove_bloatware(line, fast);
    }
}
