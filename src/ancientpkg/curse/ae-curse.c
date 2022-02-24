/* AE = [A]ncient [E]gypt */
#ifndef OMIT_ANCIENT_EGYPT_CURSE

#include <ancientpkg.h>
#include <assert.h>
#include <common/utils.h>
#include <cursedpkg.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

int cmit_ancient_egypt_curse(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    if (strncasecmp(dcf->location, "Egypt", 6) != 0)
    {
        return 0;
    }

    int curse_class = randint(1, 10);

    assert(curse_class > 0);
    assert(curse_class <= 10);

    printf(WARN "Current package contains an ancient Egyptian curse of "
                "class %d.\n",
           curse_class);

    int j = randint(40, 100);
    int k = j * curse_class;

    for (int i = 0; i < k; i++)
    {
        printf("[Decon] Removing curse from package (step %d of %d).\n", i, k);
    }

    return 0;
}

#endif