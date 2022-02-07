#include <stdio.h>
#include "rmbloatapi.h"
#include "rmbloat-common.h"
#include "csv.h"
#include "utils.h"

static int fast = 0;

void print_help()
{
    printf(
        "rmbloat - remove bloated software or any software you don't like\n\n"

        "    -h, --help           Program help\n"
        "    -f, --file           Filepath of CSV file\n"
    );
    printf("\n");
}

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

void rm_bloat_csv(char* file)
{
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

        for (int i = 10; i > 0; i--)
        {
            printf("Starting removal in %d seconds.              \r", i - 1);
            fflush(stdout);
            msleep(1000);
        }
        printf("                                                          \r");

        char* line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            char** rm_pkgs = parse_csv(line);

            if (LEN(rm_pkgs) != 1)
            {
                fprintf(stderr, "fatal: list of packages to remove "
                                "must be separated by lines");
            }
            else
            {
                char* pkg = rm_pkgs[0];
                pkg[strcspn(pkg, "\r\n")] = 0;
                remove_bloatware(pkg, fast);
            }
        }
    }
}


int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("No arguments specified.\n");
        print_help();
        exit(1);
    }


    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
        {
            print_help();
            exit(0);
        }
        else if (!strcmp(argv[i], "--fast"))
        {
            fast = 1;
        }
        else if (!strcmp(argv[i], "--file") || !strcmp(argv[i], "-f"))
        {
            i++;
            char* file = argv[i];
            rm_bloat_csv(file);
        }
        else
        {
            handle_bad_arg(argv[i]);
        }
    }
}