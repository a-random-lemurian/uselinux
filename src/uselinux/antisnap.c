#include "uselinuxcommon.h"
#include <common/argparse.h>
#include <stddef.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int anger_lvl = -1;
    int use_old_method = 0;
    char *distro;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_INTEGER('a', "anger-level", &anger_lvl,
                    "Anger level towards snaps"),
        OPT_STRING('d', "distro", &distro, "Linux distribution"),
        OPT_BOOLEAN('O', "old", &use_old_method,
                    "Call old method to snap at snaps"),
        OPT_END()};
    const char *usages[] = {"antisnap [--anger-level=LVL] [--distro=DISTRO]", NULL};
    argparse_init(&argparse, options, usages, 0);

    if (argc == 1)
    {
        argparse_help_cb(&argparse, options);
    }

    argparse_parse(&argparse, argc, (const char **)argv);

    if (use_old_method)
    {
        snap_at_snaps(distro);
    }
    else
    {
        if (!strncasecmp(distro, "ubuntu", 6))
        {
            printf("Snaps... they are annoying.");
        }
        else
        {
            printf(
                "You must be a Ubuntu user to snap at snaps. But, snaps suck "
                "anyway.\n");
        }
    }
}
