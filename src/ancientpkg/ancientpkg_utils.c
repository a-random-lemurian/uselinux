#include <sys/time.h>
#include <time.h>

static int dry_run;

void ancientpkg_set_dry_run(int i)
{
    dry_run = i;
}

void ancientpkg_msleep(int tms)
{
    if (dry_run)
    {
        return;
    }

    struct timeval tv;
    tv.tv_sec = tms / 1000;
    tv.tv_usec = (tms % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}
