#include <common/mtwister.h>
#include <common/utils.h>
#include <stdint.h>
#include <stdio.h>

#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "curse.h"
#include "infohazard.h"

int ih_amnestic(DigControlFlags *dcf, DigStatistics *dst)
{
    int n = randint(2, 10);

    printf(WARN "Detected amnestic of type %d in package. Leaks may cause "
                "memory loss to any nearby archaeologists.",
           n);

    ancientpkg_msleep(randint(100, 250));

    printf("Clearing archaeologists from site....\n");

    ancientpkg_msleep(randint(100, 300));

    int max = (n * 5) + randint(2, 5);
    for (int i = 0; i < max; i++)
    {
        printf("Neutralizing amnestic (%d/%d)\n", i, max);
    }

    printf("Amnestic neutralized.");
}
