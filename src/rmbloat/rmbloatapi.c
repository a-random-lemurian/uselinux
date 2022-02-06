#include "rmbloatapi.h"
#include "utils.h"
#include <stdio.h>


void remove_bloatware(char* bloatware)
{
    printf("removing %s....", bloatware);
    msleep(randint(300, 900));
    printf(" finished.");
    printf("\n");
}
