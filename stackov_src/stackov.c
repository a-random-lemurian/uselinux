#include "opener/opener.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STACKOV_SEARCH_URL "https://stackoverflow.com/search?q="

const char* mkstr(char str1[], char str2[])
{
        char* out = malloc(strlen(str1) + strlen(str2) + 1);
        strcpy(out, str1);
        strcat(out, str2);

        return out;
}

const char* help =
"Open Stack Overflow from the command-line\n\n"

"  --help        Help information\n"
"  --usage       Brief usage information\n\n"

"This tool is bundled with uselinux.\n"
"This program is licensed under the MIT license.\n";

void print_help()
{
    printf("%s",help);
}

void print_usage(char** argv)
{
    printf("Usage: %s [QUERY]\n", argv[0]);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_usage(argv);
    }

    if (!strcmp(argv[1],"--help"))
    {
        print_help();
        exit(0);
    }

    if (!strcmp(argv[1],"--usage"))
    {
        print_usage(argv);
        exit(0);
    }

    const char* stackov_url = mkstr(STACKOV_SEARCH_URL, argv[1]);

    printf("Opening %s in your browser.\n", stackov_url);
    opener(stackov_url);
}