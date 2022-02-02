#include "utils.h"

void msleep(int tms)
{
    struct timeval tv;
    tv.tv_sec = tms / 1000;
    tv.tv_usec = (tms % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}

void typewriter(const char *txt, int freq)
{
    for (int i = 0; i < strlen(txt); i++)
    {
        printf("%c", txt[i]);
        fflush(stdout);
        msleep(freq);
    }
}

int randint(int min, int max)
{
    MTRand mtw = seedRand(clock()*8*clock());
    int out = 0;

    while (out < min)
    {
        out = ceil(genRand(&mtw)*max);
    }

    return out;
}

int chartoint(char* str, int numbase)
{
    long num = strtol(str, NULL, numbase);
    return (int)num;
}

void trigger_segfault()
{
    char* segfault = "segfault";
    segfault[0]= 'S';
}
