#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rmbloat.h"

#ifndef USELINUX_RMBLOAT_NOCOLOR
#define BOLDGREEN "\033[1m\033[92m"
#define NOCOLOR "\033[0m"
#else
#define BOLDGREEN ""
#define NOCOLOR ""
#endif

struct cmd_struct
{
    const char *cmd;
    int len;
    int (*fn)(int, const char **);
    const char *help;
};

static struct cmd_struct subcommands[] = {
    {"from-file", 8, rmbloat_from_file,
     "Remove bloated packages listed in a file"},
    {"rm", 2, rmbloat_rm, "Remove bloated packages from the command line"}};

#define ARRSZ(a) sizeof(a) / sizeof(a[0])

int main(int argc, char **argv)
{
    int flag_help = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        /* we don't want to exit after printing help, we
           have to print the subcommand information too,
           therefore we don't use OPT_HELP() */
        OPT_BOOLEAN('h', "help", &flag_help,
                    "show this help message and exit"),
        OPT_END()};
    const char *usages[] = {
        "rmbloat rm [--help] [--fast] [<PACKAGES>]",
        "rmbloat from-csv [--help] [--wait] [--fast] --file=FILE", NULL};
    argparse_init(&argparse, options, usages, ARGPARSE_STOP_AT_NON_OPTION);
    argc = argparse_parse(&argparse, argc, (const char **)argv);

    if (flag_help || !argc)
    {
        argparse_help_cb_no_exit(&argparse, options);

        printf("\n\nSubcommands:\n");
        for (int i = 0; i < ARRSZ(subcommands); i++)
        {
            printf("   " HYEL "%s: " NOCOLOR " %s\n", subcommands[i].cmd,
                   subcommands[i].help);
        }
        exit(0);
    }

    struct cmd_struct *cmd = NULL;
    for (int i = 0; i < ARRSZ(subcommands); i++)
    {
        if (!strcmp(subcommands[i].cmd, argv[0]))
        {
            cmd = &subcommands[i];
        }
    }
    if (cmd)
    {
        return cmd->fn(argc, (const char **)argv);
    }
    return 0;
}