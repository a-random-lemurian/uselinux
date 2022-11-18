#include <common/argparse.h>
#include <common/macros.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char *usages[] = {
    "ancientpkg excavate [--target=TARGET] [<FLAGS>]", NULL};

static char *opts[] = {};

typedef struct arguments
{
    char *target;
    int attempts;
    int dry_run;
} arguments;

void init_args(arguments *arg)
{
    arg->attempts = -1;
    arg->target = NULL;
    arg->dry_run = 0;
}

int cmd_excavate(int argc, char **argv)
{
    arguments args;
    init_args(&args);

    struct argparse ap;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_STRING('t', "target", &args.target, "Target package to find."),
        OPT_INTEGER('a', "attempts", &args.attempts,
                    "Number of attempts to make while trying to find package"),
        OPT_BOOLEAN('n', "dry-run", &args.dry_run,
                    "Dry run (don't wait)"),
        OPT_END()};

    argparse_init(&ap, options, usages, 0);
    argparse_describe(&ap, "Excavate a specific package.",
                      "Compiled "__DATE__
                      " "__TIME__
                      ".");
    argparse_parse(&ap, argc, (const char **)argv);

    if (args.target == NULL)
    {
        printf(ERROR "need to specify a target package.\n");
    }

    if (args.attempts == -1)
    {
        printf(WARN "number of attempts to make not specified, assuming "
                    "infinity\n");
    }

    MTRand mtw = seed_rand(clock());

    int i = 0;
    int package_found = 0;
    while (package_found == 0)
    {
        printf("Checking source %10d "
               "(%.12ld:%.12ld:%.12ld:%.12ld:%.12ld:%.12ld:%.12ld:%.12ld:"
               "%.12ld:%.12ld:%.12ld:%.12ld)\n",
               i, gen_rand_long(&mtw), gen_rand_long(&mtw), gen_rand_long(&mtw),
               gen_rand_long(&mtw), gen_rand_long(&mtw), gen_rand_long(&mtw),
               gen_rand_long(&mtw), gen_rand_long(&mtw), gen_rand_long(&mtw),
               gen_rand_long(&mtw), gen_rand_long(&mtw), gen_rand_long(&mtw));
        i++;

        if (i > args.attempts && args.attempts != -1)
        {
            printf(ERROR "Reached maximum attempts.\n");
            exit(1);
        }

        if (args.dry_run)
        {
            msleep(randint(30, 90));
        }

        if (randint(1, 1000) > 950)
        {
            printf("Package %s was found.\n", args.target);
            package_found = 1;
        }
    }

    return 0;
}
