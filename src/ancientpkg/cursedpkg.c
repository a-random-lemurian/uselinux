#include "ancientpkg.h"
#include "cursedpkg.h"
#include <common/utils.h>
#include <stdio.h>
#include <stdint.h>

int cmit_diseased_pkg(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "package is diseased.");

    int infectionlvl = 1000;

    for (int i = 0; infectionlvl > 1; i++)
    {
        printf("Decontamination attempt %d.... (infection: %d)\n",
               i, infectionlvl);
        infectionlvl -= randint(1, 60);

        if (!dcf->dry_run)
        {
            msleep(randint(20, 135));
        }
    }

    return 0;
}
