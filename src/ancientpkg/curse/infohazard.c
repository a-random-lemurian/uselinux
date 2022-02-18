#include <ancientpkg.h>
#include <cursedpkg.h>
#include <common/utils.h>
#include <stdio.h>
#include <stdint.h>

int cmit_infohazard(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    printf(WARN "package contains an infohazard.\n");
    printf(WARN "To prevent infohazard harm, hiding output.\n");

    uint64_t n = 0;

    for (int i = 0; i < randint(30, 140); i++)
    {
        if (!dcf->dry_run)
        {
            msleep(randint(40, 90));
        }
    }

    return 0;
}