#include <common/opener.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/argparse.h>

#define STACKOV_SEARCH_URL "https://stackoverflow.com/search?q="

const char *mkstr(char str1[], char str2[])
{
    char *out = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(out, str1);
    strcat(out, str2);

    return out;
}

int main(int argc, char **argv)
{
    char *query = "";
    int flag_dry_run = 0;

    struct argparse parser;
    struct argparse_option opts[] = {
        OPT_HELP(), OPT_STRING('q', "query", &query, "Stack Overflow query"),
        OPT_BOOLEAN(0, "dry-run", &flag_dry_run,
                    "Dry run - don't open "
                    "Stack Overflow"),
        OPT_END()};

    static const char *const usage[] = {"stackov -q QUERY [--dry-run]", NULL};

    argparse_init(&parser, opts, usage, 0);
    argparse_describe(&parser, "Open Stack Overflow from the command line",
                      "\nCompiled "__DATE__
                      " "__TIME__
                      ".\n"
                      "Created by Lemuria as part of uselinux:\n"
                      "<https://github.com/a-random-lemurian/uselinux>");
    argparse_parse(&parser, argc, (const char **)argv);

    const char *stackov_url = mkstr(STACKOV_SEARCH_URL, query);

    printf("Opening %s in your browser.\n", stackov_url);

    if (!flag_dry_run)
    {
        opener(stackov_url);
    }
}
