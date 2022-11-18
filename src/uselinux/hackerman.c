/**
 * @file hackerman.c
 * @author Lemuria
 * @brief Hackerman mode.
 * @date 2022-11-18
 * 
 * @copyright MIT License
 * 
 * Legal disclaimer: Does not actually hack UNATCO, Area 51, the Statue of
 * Liberty, the Illuminati, or your local bank.
 */

#include "hackerman.h"
#include <common/utils.h>

static char* places_to_hack[] = {
    "UNATCO", "AREA 51", "STATUE OF LIBERTY",
    "ILLUMINATI", "BANKS"
};

void hackerman_mode()
{
    printf("AUGMENTATIONS ACTIVATED\n");
    printf("HACKING IN PROGRESS\n");

    for (size_t i = 0; i < LEN(places_to_hack); i++)
    {
        printf("%s...", places_to_hack[i]);
        msleep(randint(140, 280));
        printf("HACKED\n");
    }
}

void hackerman(char *distro)
{
    if (!strcasecmp(distro, "kali"))
    {
        printf("Activating Hackerman mode....\n");
        hackerman_mode();
    }
    else
    {
        printf("fatal: --hackerman requires Kali Linux (use -d kali)\n");
        exit(1);
    }
}
