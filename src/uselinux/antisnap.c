#include "uselinuxcommon.h"
#include <common/argparse.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

char* anti_snap_message(int anger_lvl)
{
    char out[256];

    if (anger_lvl < 10)
    {
        sprintf(out, "Snaps... they are annoying.\n");
    }
    else if (anger_lvl < 50)
    {
        sprintf(out, "Reject snap! Return to apt!\n");
    }
    else if (anger_lvl < 100)
    {
        sprintf(out, "Warning: too angry.\n");
    }
    else if (anger_lvl < 200)
    {
        sprintf(out, "Okay, we get it. Snaps are evil.\n");
    }
    else if (anger_lvl > 201)
    {
        sprintf(out, "Are you really angry at snaps? That's a high anger "
               "level. (%d)\n",
               anger_lvl);
    }

    return (char*)out;
}

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
    const char *usages[] = {"antisnap [--anger-level=LVL] [--distro=DISTRO]",
                            NULL};
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
            printf("%s", anti_snap_message(anger_lvl));
        }
        else
        {
            printf(
                "You must be a Ubuntu user to snap at snaps. But, snaps suck "
                "anyway.\n");
        }
    }
}
