#include <ancientpkg.h>
#include <common/ansiescapes.h>
#include <common/argparse.h>
#include <common/mtwister.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Subcommand subcommands[] = {
    {"dig", cmd_dig, "Dig for ancient packages"},
    {"date", cmd_date, "Determine the age of a package"},
    {"excavate", cmd_excavate, "Excavate a single package"},
    {"install", cmd_install, "Install extracted packages"}};

int main(int argc, char **argv)
{
    int flag_help = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_BOOLEAN('h', "help", &flag_help, "show this message and exit"),
        OPT_END()};
    const char *usages[] = {"ancientpkg [<subcommand>]", NULL};
    argparse_init(&argparse, options, usages, ARGPARSE_STOP_AT_NON_OPTION);
    argc = argparse_parse(&argparse, argc, (const char **)argv);
    if (argc == 0 || flag_help)
    {
        argparse_help_cb_no_exit(&argparse, options);

        printf("\n\nSubcommands:\n");
        for (int i = 0; i < sizeof(subcommands) / sizeof(subcommands[0]); i++)
        {
            printf("   " HYEL "%s" reset ": %s\n", subcommands[i].cmd,
                   subcommands[i].help);
        }
        exit(0);
    }

    Subcommand *cmd = NULL;
    for (int i = 0; i < sizeof(subcommands) / sizeof(subcommands[0]); i++)
    {
        if (!strcmp(subcommands[i].cmd, argv[0]))
        {
            cmd = &subcommands[i];
        }
    }
    if (cmd)
    {
        return cmd->fn(argc, argv);
    }
    return 0;
}
