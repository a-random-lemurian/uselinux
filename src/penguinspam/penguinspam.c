/**
 * @file penguinspam.c
 * @author Lemuria
 * @brief Implementation file for penguin spam.
 * @date 2022-02-04
 *
 * @copyright MIT License
 *
 */

#include "penguinspam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <common/utils.h>

#define LOGGER_NAME "penguinspam"
#include <common/log.h>

// penguinspam Internals //////////////////////////////////////////////////////

char *_get_linux_distro()
{
    char *distro = malloc(64);

    char distros[][64] = {
        "MX Linux",     "EndeavourOS", "Manjaro",       "Mint",
        "Pop!_OS",      "Ubuntu",      "Debian",        "Garuda",
        "elementary",   "Fedora",      "Zorin",         "openSUSE",
        "Slackware",    "Lite",        "Solus",         "PCLinuxOS",
        "Kali",         "Kubuntu",     "ArcoLinux",     "SparkyLinux",
        "Arch",         "Artix",       "Puppy",         "Q4OS",
        "CentOS",       "Linuxfx",     "Devuan",        "Alpine",
        "Lubuntu",      "EasyOS",      "Void",          "Rocky",
        "GhostBSD",     "Tails",       "AlmaLinux",     "Bluestar",
        "Nitrux",       "PureOS",      "Peppermint",    "Feren",
        "Xubuntu",      "Mageia",      "ReactOS",       "Kodachi",
        "Gentoo",       "NixOS",       "deepin",        "RebornOS",
        "Voyager",      "Mabox",       "Bodhi",         "Qubes",
        "Trisquel",     "Red Hat",     "Ubuntu MATE",   "4MLinux",
        "KaOS",         "Parrot",      "Lakka",         "Gecko",
        "Emmabuntüs",   "EuroLinux",   "Tiny Core",     "RasPiOS",
        "DragonFly",    "KNOPPIX",     "BunsenLabs",    "Haiku",
        "Clear",        "Archcraft",   "SteamOS",       "Archman",
        "SystemRescue", "NuTyX",       "Ubuntu Budgie", "Ubuntu Studio",
        "CloudReady",   "ROSA",        "Septor",        "JingOS",
        "Redcore",      "AV Linux",    "Robolinux",     "siduction",
        "Freespire",    "UBports"};

    if (distro != NULL)
    {
        strcpy(distro, distros[randint(1, LEN(distros)) - 1]);
    }
    else
    {
        log_fatal("Memory allocation failure!");
        abort();
    }

    return distro;
}

int _is_valid_penguin(char *penguin_type)
{
    const char valid_penguins[][16] = {"emperor",    "snares", "little",
                                       "yelloweyed", "gentoo", "african",
                                       "mixed"};

    for (int i = 0; i < LEN(valid_penguins); i++)
    {
        if (!strcasecmp(penguin_type, valid_penguins[i]))
        {
            return 1;
        }
        else
        {
            continue;
        }
    }

    return 0;
}

// Public API /////////////////////////////////////////////////////////////////

void free_psj_mem(penguin_spam_job *job) { free(job->__error__); }

int mk_penguin_spam_job(penguin_spam_job *job, int penguins, char *location,
                        char *penguin_type)
{
    job->__error__ = malloc(512);

    if (!strcmp(location, ""))
    {
        sprintf(job->__error__, "Error: Location cannot be an empty string");
        return PENGUIN_SPAM_ERROR;
    }
    if (penguins > MAX_PENGUINS)
    {
        sprintf(job->__error__,
                "Error: Too many penguins (limit is %d, "
                "tried to send %d)",
                MAX_PENGUINS, penguins);
        return PENGUIN_SPAM_TOO_MANY_PENGUINS;
    }
    if (penguins <= 0)
    {
        sprintf(job->__error__,
                "Error: penguins must be a positive number (tried to send %d)",
                penguins);
        return PENGUIN_SPAM_ERROR;
    }
    if (!_is_valid_penguin(penguin_type))
    {
        sprintf(job->__error__,
                "Error: penguin type %s is invalid. Must be of: african, "
                "gentoo, yelloweyed, little, snares, emperor",
                penguin_type);
        return PENGUIN_SPAM_INVALID_PENGUIN;
    }

    penguin_food food;
    prepare_penguin_food("squid", &food, penguins * 3, job);

    job->location = location;
    job->penguins = penguins;

    return PENGUIN_SPAM_OK;
}

int execute_penguin_spam_job(penguin_spam_job *job)
{
    log_info("Acquired penguins.");
    log_info("Sending %d penguins to %s, done.", job->penguins, job->location);

    if (job->penguins >= 1000000)
    {
        log_warn("More than 1 million penguins. Lowering verbosity.");
    }
    else
    {
        for (int i = 0; i < job->penguins; i++)
        {
            if (randint(1, 100000) > 99990)
            {
                log_error(
                    "%d: Corrupted partition caused by minor penguin action.",
                    i);
            }
            else if (randint(1, 100000) > 86800)
            {
                char *distro = _get_linux_distro();
                log_warn("%d: Microsoft employee refused to accept copy of %s "
                         "from penguin.",
                         i, distro);
                free(distro);
            }
            else if (randint(1, 100000) > 43000)
            {
                char *distro = _get_linux_distro();
                log_info("%d: Convinced person to switch to %s successfully!",
                         i, distro);
                free(distro);
            }
            else
            {
                continue;
            }
        }
    }

    log_info("Successfully spammed penguins.");

    return PENGUIN_SPAM_OK;
}

int finish_penguin_spam_job(penguin_spam_job *job)
{
    free(job->__error__);
    return PENGUIN_SPAM_OK;
}

int check_food_type(char *type)
{
    if (!strcasecmp(type, "squid"))
    {
        return 10;
    }
    else if (!strcasecmp(type, "fish"))
    {
        return 5;
    }
    else if (!strcasecmp(type, "krill"))
    {
        return 2;
    }
    else
    {
        fprintf(stderr, "penguinspam: invalid food type %s", type);
        abort();
    }
}

/**
 * @brief Perform computationally-expensive math calculations, which will
 * cause small amounts of CPU heat. The heat is then teleported to a large
 * facility on Earth cooking the desired food for all the penguins before
 * they embark on their penguin spam expedition.
 *
 * @param type Type of penguin food.
 */
void cook_penguin_food(char *type)
{
    int type_int = check_food_type(type);
    for (int i = 0; i < type_int; i++)
    {
        double n;
        for (double j = 0; j < 10; j++)
        {
            n = sin(j);
        }
    }
}

int prepare_penguin_food(char *type, penguin_food *food, int qty,
                         penguin_spam_job *job)
{
    for (int i = 0; i < qty; i++)
    {
        cook_penguin_food(type);
    }
    food->food = type;
    food->qty = qty;
    job->food = *food;
    return PENGUIN_SPAM_OK;
}
