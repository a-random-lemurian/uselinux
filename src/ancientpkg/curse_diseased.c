#include <common/utils.h>
#include <stdint.h>
#include <stdio.h>

#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "curse.h"

int cmit_diseased_pkg(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "package is diseased.");

    int infectionlvl = 1000;

    for (int i = 0; infectionlvl > 1; i++)
    {
        printf("Decontamination attempt %d.... (infection: %d)\n", i,
               infectionlvl);
        infectionlvl -= randint(1, 60);

        ancientpkg_msleep(randint(20, 135));
    }

    return 0;
}
