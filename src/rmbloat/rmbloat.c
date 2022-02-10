#include <stdio.h>
#include <stdlib.h>
#include <argparse.h>
#include <string.h>

#include "rmbloat.h"

#ifndef USELINUX_RMBLOAT_NOCOLOR
#define BOLDGREEN "\033[1m\033[92m"
#define NOCOLOR "\033[0m"
#else
#define BOLDGREEN ""
#define NOCOLOR ""
#endif

struct cmd_struct {
    const char *cmd;
    int len;
    int (*fn) (int, const char **);
    const char *help;
};


static struct cmd_struct subcommands[] = {
    {"from-csv", 8, rmbloat_csv, "Remove bloated packages listed in a file"},
    {"rm", 2, rmbloat_rm, "Remove bloated packages from the command line"}
};


int main(int argc, char** argv)
{
    if (argc == 2 && !strcmp(argv[1], "--help"))
    {
        printf(
            "Usage: %s [--help] <command> [<args>]\n"
            "\n"
            "Subcommands:\n"
            "\n"
            , argv[0]);
        int i;
        for (i = 0; i < sizeof(subcommands)/sizeof(subcommands[0]); i++)
        {
            printf("    "BOLDGREEN"%s"NOCOLOR": %s\n",
                   subcommands[i].cmd,
                   subcommands[i].help);
        }
        printf("\n");
        exit(0);
    }
    else if (argc == 1)
    {
        printf("For help, try %s --help.\n", argv[0]);
    }
    else
    {
        long subcmd_ls_sz = sizeof(subcommands)/sizeof(subcommands[0]);
        int i;
        for (i = 0; i < subcmd_ls_sz; i++)
        {
            char** subcmd_argv;
            if (!strcmp(argv[1], subcommands[i].cmd))
            {
                subcommands[i].fn(argc, (const char**)argv);
            }
        }
    }
}