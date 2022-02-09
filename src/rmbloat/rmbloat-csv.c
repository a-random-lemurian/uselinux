#include <stdio.h>
#include "rmbloatapi.h"
#include "rmbloat-common.h"
#include "csv.h"
#include "utils.h"
#include "argparse.h"

int fast;

void print_help()
{
    printf(
        "rmbloat - remove bloated software or any software you don't like\n\n"
        );
}

static const char *const usage[] = {
    "rmbloat-csv [options] [[--] args]",
    "rmbloat-csv [options]",
    NULL,
};


size_t line_cnt(char* file)
{
    size_t linecnt = -1;
    FILE* fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "fatal: unable to find file %s\n", file);
        exit(1);
    }
    else
    {
        char* line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            linecnt++;
        }
    }

    return linecnt;
}

int csv_line_len(char** csv)
{
    int i = 0;
    while (csv[i] != NULL)
    {
        i++;
    }

    return i;
}

int check_single_line(char** csv, int linepos)
{
    if (csv_line_len(csv) != 1)
    {
        fprintf(stderr, "fatal: list of packages to remove "
                        "must be separated by lines (line %d)", linepos);
        return 1;
    }
    return 0;
}

void check_bloat_csv_list(char* file)
{
    FILE* fp = fopen(file, "r");
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int linepos = 1;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        char** csv = parse_csv(line);
        if (!check_single_line(csv, linepos))
        {
            fclose(fp);
            exit(1);
        }
        linepos++;
    }
    fclose(fp);
}

void rm_bloat_csv(char* file, int wait)
{
    check_bloat_csv_list(file);
    FILE* fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "fatal: unable to find file %s\n", file);
        exit(1);
    }
    else
    {
        size_t lines = line_cnt(file);
        printf("Packages to remove: %ld.\n", lines);

        if (wait)
        {
            for (int i = 10; i > 0; i--)
            {
                printf("Starting removal in %d seconds.              \r",
                       i - 1);
                fflush(stdout);
                msleep(1000);
            }
            printf("                                                  "
                   "        \r");
        }

        char* line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            char** rm_pkgs = parse_csv(line);
            char* pkg = rm_pkgs[0];
            pkg[strcspn(pkg, "\r\n")] = 0;
            remove_bloatware(pkg, fast);
        }
    }
}

int main(int argc, const char** argv)
{
    if (argc == 1)
    {
        printf("No arguments specified.\n");
        exit(1);
    }

    int wait = 0;
    int fast = 0;
    char* file;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('w', "wait", &wait, "wait 10 seconds before starting"),
        OPT_BOOLEAN('s', "fast", &fast, "remove bloat faster"),
        OPT_STRING('f', "file", &file, "path to CSV file"),
        OPT_END()
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, "\nRemove bloated packages from a list in a file.", "\n-");
    argc = argparse_parse(&argparse, argc, argv);

    printf("%s",file);

    rm_bloat_csv(file, wait);

}