#include "ancientpkg.h"
#include "ancientpkg_utils.h"
#include "curse.h"
#include <common/utils.h>
#include <common/mtwister.h>
#include <stdio.h>
#include <stdint.h>
#include "infohazard.h"

static Infohazard infohazards[] = {
    {10, "Berryman-Langford Memetic Kill Agent", ih_berryman_langford},
    {6, "Amnestics", ih_amnestic}
};

int random_infohazard(DigControlFlags *dcf, DigStatistics *dst)
{
    size_t ih_sz = sizeof(infohazards)/sizeof(infohazards[0]);
    size_t idx = randint(1, ih_sz) - 1;

    print_infohazard_message(&infohazards[idx]);
    
    Infohazard* detected_infohazard = &infohazards[idx];

    detected_infohazard->fn(dcf, dst);
}

int cmit_infohazard(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "package contains an infohazard.\n");
    printf(WARN "To prevent infohazard harm, hiding output.\n");

    int lvl = randint(1, 10);

    uint64_t bytes_suppressed = lvl * 50 * randint(20, 50) * 900 * (clock()/2);

    ancientpkg_msleep(randint(40, 90));
    random_infohazard(dcf, dst);

    printf("%lu bytes of infohazardous memory was suppressed.\n",
           bytes_suppressed);

    return 0;
}

int print_infohazard_message(Infohazard* ih)
{
    printf(WARN "Infohazard %s with danger level %d detected.\n",
           ih->name, ih->danger);
    return 0;
}
