#include "deskenv.h"

#include <common/log.h>
#include <common/utils.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOGGER_NAME "deskenv"

void sigint_handler()
{
    log_fatal("SIGINT recieved");
    exit(1);
}

void desktop_environments(char *desk)
{
    signal(SIGINT, sigint_handler);

    if (!strcasecmp(desk, "gnome"))
    {
        log_info("GNOME desktop detected.");
        log_warn("GNOME desktop is causing the CPU to overheat!");
        for (int i = 0; i < randint(30, 70); i++)
        {
            log_warn("CPU Temperature (celsius): %d", randint(50, 80));
            msleep(randint(12, 55));
        }
        if (randint(1, 800) >= 400)
        {
            log_info("Activating emergency cooling system.");

            for (int i = 0; i < randint(6, 8); i++)
            {
                log_info("Successfully redirected Coolant Source %d.", i + 1);
                msleep(randint(100, 4000));
            }

            log_info("Prevented CPU overheat. Maybe don't run GNOME, eh?");

            return;
        }
        else
        {
            log_fatal("CPU has overheated because of GNOME! (Just kidding.)");
        }

        exit(1);
    }
    else if (!strcasecmp(desk, "kde"))
    {
        log_info("KDE desktop detected.");

        if (randint(1, 900) >= 800)
        {
            log_warn("KDE is too much bloat.");
            log_fatal("uselinux could not withstand the bloat of KDE.");
        }
        else
        {
            log_info("KDE is not bloated.");
        }
    }
}
