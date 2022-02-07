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
    char buf[512];
    int rc = readlink("/proc/self/exe", buf, 64);

    if (argc == 1)
    {
        printf("No arguments specified.\n");
        print_help();
        exit(1);
    }

    int pass_to_subcommand = 0;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
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
        else if (!strcmp(argv[i], "from-csv") && i == 1)
        {
            strcat(buf, "-csv ");
            pass_to_subcommand = 1;
        }
        else if (!strcmp(argv[i], "rm") && i == 1)
        {
            strcat(buf, "-rm ");
            pass_to_subcommand = 1;
        }
        else if (pass_to_subcommand)
        {
            strcat(buf, argv[i]);
            strcat(buf, " ");
        }
        else
        {
            handle_bad_arg(argv[i]);
        }
    }

    rc = system(buf);
}