#include "deskenv.h"

#include <common/log.h>
#include <common/utils.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define LOGGER_NAME "deskenv"

void sigint_handler()
{
    log_fatal("SIGINT recieved");
    exit(1);
}

int redirect_one_coolant_source(int i)
{
    msleep(randint(145, 287));
    if (randint(1, 10) > 5)
    {
        log_info("Successfully redirected Coolant Source %d.", i + 1);
        return 1;
    }
    else
    {
        log_error("Failed to redirect Coolant Source %d.", i + 1);
        return 0;
    }
}

int redirect_coolant_sources(int coolant_sources, int required)
{
    int activated = 0;

    for (int i = 0; i < coolant_sources; i++)
    {
        if (redirect_one_coolant_source(i))
        {
            activated++;
        }
    }

    if (activated >= required)
    {
        return 1;
    }

    return 0;
}

void desktop_environment_gnome_cooling_sys()
{
    log_info("Activating emergency cooling system.");

    int coolant_sources = randint(5, 10);
    int required = randint(2, 4);

    int rc = redirect_coolant_sources(coolant_sources, required);

    if (rc)
    {
        log_info("Prevented CPU overheat. Maybe don't run "
                 "GNOME, eh?");
    }
    else if (!rc)
    {
        log_fatal("CPU has overheated because of GNOME! "
                  "(Just kidding.)");
        exit(0);
    }
}

void desktop_environment_gnome()
{
    log_info("GNOME desktop detected.");
    log_warn("GNOME desktop is causing the CPU to overheat!");
    
    int cpu_temp = randint(10, 20);
    int max_cpu_temp = randint(80, 130);

    for (;;)
    {
        log_warn("CPU Temperature (celsius): %d", cpu_temp);

        cpu_temp += randint(3, 8);

        msleep(randint(12, 55));

        if (cpu_temp >= max_cpu_temp)
        {
            desktop_environment_gnome_cooling_sys();
            break;
        }
    }
}

void desktop_environment_kde()
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


void desktop_environment_xfce()
{
    log_info("Xfce desktop detected.");
}

void desktop_environment_unity()
{
    log_info("Unity desktop detected.");
}

static struct uselinux_de deskenvs[] = {
  {"gnome", desktop_environment_gnome },
  {"kde",   desktop_environment_kde   },
  {"xfce",  desktop_environment_xfce  },
  {"unity", desktop_environment_unity },
};

void desktop_environments(char *desk)
{
    signal(SIGINT, sigint_handler);

    for (size_t i = 0; i < LEN(deskenvs); i++)
    {
        printf("%d\n",i);
        if (!strcasecmp(desk, deskenvs[i].string))
        {
            deskenvs[i].responder();
            return;
        }
    }
}
