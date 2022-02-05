#include "deskenv.h"
#include "log.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LOGGER_NAME "deskenv"

void desktop_environments(char* desk)
{
    if (!strcasecmp(desk, "gnome"))
    {
        log_info("GNOME desktop detected.");
        log_warn("GNOME desktop is causing the CPU to overheat!");
        for (int i = 0; i < randint(30,70); i++)
        {
            log_warn("CPU Temperature (celsius): %d", randint(50, 80));
            msleep(randint(12,55));
        }
        if (randint(1, 800) >= 400)
        {
            log_info("Activating emergency cooling system.");

            for (int i = 0; i < randint(6, 8); i++)
            {
                log_info("Successfully redirected Coolant Source %d.", i+1);
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
}
