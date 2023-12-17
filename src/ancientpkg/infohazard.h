#ifndef INFOHAZARD_H
#define INFOHAZARD_H
#include "ancientpkg.h"

typedef struct Infohazard
{
    int danger;
    char *name;
    int (*fn)(DigControlFlags *, DigStatistics *);
} Infohazard;

int ih_berryman_langford(DigControlFlags *dcf, DigStatistics *dst);
int ih_amnestic(DigControlFlags *dcf, DigStatistics *dst);
int print_infohazard_message(Infohazard *ih);

#endif /* INFOHAZARD_H */
