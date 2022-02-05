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

void typewriter_randomized(const char *txt, int min, int max)
{
    for (int i = 0; i < strlen(txt); i++)
    {
        printf("%c", txt[i]);
        fflush(stdout);
        msleep(randint(min, max));
    }
}

int randint(int min, int max)
{
    MTRand mtw = seedRand(clock());
    int out = 0;

    while (out < min)
    {
        out = ceil(genRand(&mtw) * max);
    }

    return out;
}

int chartoint(char *str, int numbase)
{
    long num = strtol(str, NULL, numbase);
    return (int)num;
}

void trigger_segfault()
{
    char *segfault = "segfault";
    segfault[0] = 'S';
}

void segfault_or_abort(int threshold)
{
    int finalthreshold = 250;

    if (threshold == 500)
    {
        abort();
    }
    else if (threshold == 0)
    {
        trigger_segfault();
    }

    if (threshold >= 0 && threshold <= 500)
    {
        finalthreshold = threshold;
    }

    if (randint(0, 500) >= finalthreshold)
    {
        abort();
    }
    else
    {
        trigger_segfault();
    }
}

struct tm get_time()
{
    time_t s = 1;
    struct tm *current_time;
    s = time(NULL);
    current_time = localtime(&s);

    return *current_time;
}
