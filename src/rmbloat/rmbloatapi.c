#include "rmbloatapi.h"
#include "utils.h"
#include <stdio.h>


void remove_bloatware(char* bloatware)
{
    printf("removing %s....", bloatware);
    for (int i = 0; i < 65 - strlen(bloatware); i++)
    {
        printf(" ");
    }
    fflush(stdout);

    int sleep = randint(300, 900);
    msleep(sleep);
    printf(" finished in %d ms.", sleep);
    printf("\n");
}
