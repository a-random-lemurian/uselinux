#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include <string.h>
#include "rmbloat-common.h"


void print_help()
{
    printf(
        "rmbloat - remove bloated software or any software you don't like\n\n"

        "    -h, --help           Program help\n\n"

        "Subcommands:\n"
        "    rm               Remove bloat from the command line\n"
        "    from-csv         Remove a list of packages from a file \n"
        "                     separated by newlines\n"
    );
    printf("\n");
}


/* Look for executables in the same directory as the executable itself. */


int main(int argc, char** argv)
{
    char* buf = malloc(512);
    int rc = readlink("/proc/self/exe", buf, 64);

    if (argc == 1)
    {
        printf("No arguments specified.\n");
        print_help();
        exit(1);
    }

    char* subcmd = "";
    int pass_to_subcommand = 0;
    int rm_l_flag =0;
    for (int i = 1; i < argc; i++)
    {
        if (!strncmp(argv[i], "--help", 7) || !strncmp(argv[i], "-h", 2))
        {
            if (!pass_to_subcommand)
            {
                print_help();
                exit(0);
            }
            else
            {
                strcat(buf, argv[i]);
            }
        }
        else if (!strncmp(argv[i], "from-csv", 9) && i == 1)
        {
            strcat(buf, "-csv ");
            subcmd = "csv";
            pass_to_subcommand = 1;
        }
        else if (!strncmp(argv[i], "rm", 2) && i == 1)
        {
            strcat(buf, "-rm ");
            subcmd = "rm";
            pass_to_subcommand = 1;
        }
        else if (pass_to_subcommand)
        {
            if (!strncmp(argv[i], "-l", 2) && !strcmp(subcmd, "rm"))
            {
                strcat(buf, "-l ");
                rm_l_flag = 1;
                continue;
            }
            if (rm_l_flag)
            {
                strcat(buf, "\"");
            }
            strcat(buf, argv[i]);
            if (rm_l_flag)
            {
                strcat(buf, "\"");
            }
            strcat(buf, " ");
        }
        else
        {
            handle_bad_arg(argv[i]);
        }
    }

    rc = system(buf);
    free(buf);
}