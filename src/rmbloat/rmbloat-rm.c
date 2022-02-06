#include <argp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rmbloat-common.h"
#include "rmbloatapi.h"

void print_help()
{
    printf(
        "rmbloat-rm - remove bloatware\n\n"

        "    -h, --help           Program help\n"
        "    -l, --list           List of software to remove\n"
    );
    printf("\n");
}


int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
        {
            print_help();
            exit(0);
        }
        if (!strcmp(argv[i], "--list") || !strcmp(argv[i], "-l"))
        {
            i++;
            for (int idx = i; idx < argc; idx++)
            {
                remove_bloatware(argv[idx]);
            }
            exit(0);
        }
        else
        {
            handle_bad_arg(argv[i]);
        }
    }
}