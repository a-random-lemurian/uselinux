#include "curse.h"

#include <common/ansiescapes.h>
#include <common/mtwister.h>
#include <common/utils.h>
#include <math.h>

#include "ancientpkg.h"
#include "ancientpkg_utils.h"

static PackageCurse curses[] = {
    {"disease", "Diseased package", cmit_diseased_pkg},
    {"memetic", "Infohazardous package", cmit_infohazard}

#ifndef OMIT_ANCIENT_EGYPT_CURSE
    ,
    {"ancient-egyptian-curse", "Ancient Egyptian curse",
     cmit_ancient_egypt_curse}
#endif
};

/*
 * Mitigate a package curse, by calling a function that can deploy a more
 * specialized response to the type of curse on the package.
 */
int mitigate_curse(DigStatistics *dst, DigControlFlags *dcf)
{
    MTRand mtw = seed_rand(clock());

    curses[(int)floor(gen_rand(&mtw) * (sizeof(curses) / sizeof(curses[0])))]
        .fn(0, dcf, dst);
}

/*
 * Check a package for a curse, and then call mitigate_curse() if the package
 * is detected to be cursed.
 */
int curse_check(int loops, DigStatistics *dst, DigControlFlags *dcf)
{
    if (!(randint(1, 100000)) > 91700)
    {
        return 1;
    }

    dst->cursed_packages++;

    printf("\n" WARN "curse detected in package.");
    repeat(' ', 30);
    printf("\n");

    ancientpkg_msleep((randint(35, 88)));

    int n = randint(1, 1000);

    printf(WARN "digsite %d lockdown initiated.\n", loops);

    mitigate_curse(dst, dcf);

    return 0;
}
