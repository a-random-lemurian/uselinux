#include "rmbloatapi.h"

#include <common/utils.h>
#include <stdio.h>


void remove_bloatware(char* bloatware, int fast)
{
    printf("removing %s....", bloatware);
    for (int i = 0; i < 65 - strlen(bloatware); i++)
    {
        printf(" ");
    }
    fflush(stdout);

    int sleep = 0;

    if (!fast)
    {
        sleep = randint(300, 900);
    }
    else
    {
        sleep = randint(30, 80);
    }

    msleep(sleep);
    printf(" finished in %d ms.", sleep);
    printf("\n");
}
