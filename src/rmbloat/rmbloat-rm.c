#include <argp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rmbloat-common.h"
#include "rmbloatapi.h"


static int fast_flag = 0;

void print_help()
{
    printf(
        "rmbloat-rm - remove bloatware\n\n"

        "    -h, --help           Program help\n"
        "    -l, --list           List of software to remove\n"
        "        --fast           Be faster\n"
    );
    printf("\n");
}


int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (!strncmp(argv[i], "--help", 7) || !strncmp(argv[i], "-h", 2))
        {
            print_help();
            exit(0);
        }
        else if (!strncmp(argv[i], "--list", 7) || !strncmp(argv[i], "-l", 2))
        {
            i++;
            for (int idx = i; idx < argc; idx++)
            {
                remove_bloatware(argv[idx], fast_flag);
            }
            exit(0);
        }
        else if (!strncmp(argv[i], "--fast", 7))
        {
            fast_flag = 1;
        }
        else
        {
            handle_bad_arg(argv[i]);
        }
    }
}