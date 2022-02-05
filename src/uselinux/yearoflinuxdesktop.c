#include "uselinuxcommon.h"
#include "yearoflinuxdesktop.h"
#include "utils.h"

void year_of_linux_desktop_segfault()
{
    char messages[][64] = {
        "Go back to history class!",
        "You clearly don't know anything about history.",
        "Have fun debugging with GDB!",
        "I'm sure this year will be the year of the " LINUXREF " desktop!",
        "I'm sure next year will be the year of the " LINUXREF " desktop!"};

    MTRand mtw = seedRand(clock());

    char *HISTORY_MSG = messages[(int)floor(genRand(&mtw) * LEN(messages))];

    printf("I hereby sentence you to a segfault. %s\n", HISTORY_MSG);
    trigger_segfault();
}

void year_of_linux_desktop(int currentyr, int linux_desktop_yr)
{
    if (linux_desktop_yr > ANALYTICAL_ENGINE_YEAR &&
        linux_desktop_yr < ANALYTICAL_ENGINE_YEAR + 50)
    {
        printf("Not sure if you can run %s on the Analytical Engine, that "
               "thing doesn't even support %s!",
               LINUXREF, LINUXREF);
        exit(1);
    }
    else if (linux_desktop_yr < LINUX_KERNEL_FIRST_RELEASE)
    {
        printf("%d was in the past. And that definitely "
               "wasn't the year of the %s desktop, because the Linux kernel "
               "didn't even exist back then!\n",
               linux_desktop_yr, LINUXREF);
        exit(1);
    }
    else if (linux_desktop_yr > LINUX_KERNEL_FIRST_RELEASE &&
             linux_desktop_yr < currentyr)
    {
        if (currentyr - linux_desktop_yr == 1)
        {
            printf("Last year wasn't the year of the " LINUXREF " desktop.");
        }
        else
        {
            printf("That was %d years ago. Definitely wasn't the year of "
                   "the " LINUXREF " desktop.",
                   currentyr - linux_desktop_yr);
        }
        exit(1);
    }
    else if (linux_desktop_yr > currentyr)
    {
        int diff = linux_desktop_yr - currentyr;

        if (diff == 0)
        {
            printf("Surely this is the year of the %s desktop, "
                   "right?\n",
                   LINUXREF);
        }
        else if (diff <= 1)
        {
            printf("The year of the %s desktop will be soon.", LINUXREF);
        }
        else if (diff <= 10)
        {
            printf("Microsoft Windows' market share is declining, "
                   "are you sure?");
        }
        else if (diff <= 50)
        {
            printf("Very pessimistic, indeed.");
        }
        else
        {
            printf("You can't even predict the year of "
                   "the " LINUXREF " desktop properly? Well, ");
            year_of_linux_desktop_segfault();
        }
    }
    else
    {
        year_of_linux_desktop_segfault();
    }
}

int get_year_of_linux_desktop()
{
    struct tm time = get_time();

    // randint will always return 0 if the min argument is 0,
    // so we subtract by 1 to allow 0 (therefore, the current
    // year)
    return time.tm_year + 1900 + randint(1,2) - 1;
}
