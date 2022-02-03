#include "../opener/opener.h"
#include <argp.h>
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

static struct argp_option opts[] = {
    {"search", 's', "QUERY", 0, "Search term on Stack Overflow"},
    {"dry-run", 'd', 0, 0, "Do not actually open Stack Overflow in browser"},
    {0}};

struct args
{
    char *url;

    int dry_run;
};


static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct args *arguments = state->input;

    switch (key)
    {
    case 's':
        arguments->url = arg;
        break;
    case 'd':
        arguments->dry_run = 1;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static char doc[] = "Open Stack Overflow from the command line";
static struct argp argp = {opts, parse_opt, 0, doc};

void defaults(struct args *args)
{
    args->url = NULL;
}

int main(int argc, char **argv)
{
    struct args arguments;
    defaults(&arguments);
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.url == NULL)
    {
        printf("fatal: search query not specified\n");
        exit(1);
    }

    const char* stackov_url = mkstr(STACKOV_SEARCH_URL, arguments.url);

    printf("Opening %s in your browser.\n", stackov_url);

    if (!arguments.dry_run)
    {
        opener(stackov_url);
    }
}
