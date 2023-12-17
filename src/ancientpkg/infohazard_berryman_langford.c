#include <common/mtwister.h>
#include <common/utils.h>
#include <stdint.h>
#include <stdio.h>

#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "curse.h"
#include "infohazard.h"

int ih_berryman_langford(DigControlFlags *dcf, DigStatistics *dst)
{
    int max = randint(7, 23);

    for (int i = 0; i < max; i++)
    {
        printf(WARN "Expunging data (%d/%d)\n", i, max);
        ancientpkg_msleep(randint(30, 50));
    }
}
