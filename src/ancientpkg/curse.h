#ifndef CURSEDPKG_H
#define CURSEDPKG_H
#include "ancientpkg.h"

typedef struct PackageCurse
{
    char* type;
    char* name;
    int (*fn)(int, DigControlFlags*, DigStatistics*);
} PackageCurse;

int cmit_diseased_pkg(int n, DigControlFlags *dcf, DigStatistics *dst);
int cmit_infohazard(int n, DigControlFlags *dcf, DigStatistics *dst);

#ifndef OMIT_ANCIENT_EGYPT_CURSE
int cmit_ancient_egypt_curse(int n, DigControlFlags *dcf, DigStatistics *dst);
#endif

#endif /* CURSEDPKG_H */
