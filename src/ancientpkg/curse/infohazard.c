#include <ancientpkg.h>
#include <cursedpkg.h>
#include <common/utils.h>
#include <common/mtwister.h>
#include <stdio.h>
#include <stdint.h>

int cmit_infohazard(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "package contains an infohazard.\n");
    printf(WARN "To prevent infohazard harm, hiding output.\n");

    int lvl = randint(1, 10);

    uint64_t bytes_suppressed = lvl * 50 * randint(20, 50) * 900 * (clock()/2);

    for (int i = 0; i < randint(30, 140); i++)
    {
        if (!dcf->dry_run)
        {
            msleep(randint(40, 90));
        }

    }

    printf("%lu bytes of infohazardous memory was suppressed.\n",
           bytes_suppressed);

    return 0;
}
