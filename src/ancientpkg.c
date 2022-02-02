#include <time.h>
#include <math.h>
#include <stdio.h>

#include "mtwister.h"
#include "ancientpkg.h"
#include "utils.h"

int check_digsite(int i)
{
    printf("-------- [Digsite %d] --------\n",i);
    printf("Digging for packages.... ");
    fflush(stdout);

    int packages = randint(300, 800);
    printf("found %d\n",packages);

    return packages;
}

void ancient_debian_packages()
{
    MTRand mtw = seedRand(clock()*8*clock());

    int digsites = randint(300,900);


    printf("Travelling to digsites to find ancient Debian packages.\n");

    int total_packages = 0;

    for (int i = 0; i < digsites; i++)
    {
        total_packages += check_digsite(i);
    }

    printf("Finished digging.... found %d total packages.", total_packages);
}
