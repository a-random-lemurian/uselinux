// Slightly modified by Lemuria

//
// opener.c
// Open URLS in C
//
// MIT licensed.
// Copyright (c) Abraham Hernandez <abraham@abranhe.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "detect_os.h"

char *create_cmd(const char *cmd, const char *link)
{
    char *url = malloc(strlen(cmd) + strlen(link) + 3);
    strcpy(url, cmd);
    strcat(url, link);
    return url;
}

int opener(const char *url)
{
    const char *platform = operating_system();
    const char *cmd = NULL;

    // Hanlde macOS
    if (!strcmp(platform, "macOS"))
    {
        cmd = "open";

        // Handle Windows
    }
    else if (!strcmp(platform, "win32") || !strcmp(platform, "win64"))
    {
        cmd = "start";

        // Handle Linux, Unix, etc
    }
    else if (!strcmp(platform, "unix") || !strcmp(platform, "linux") ||
             !strcmp(platform, "freeBSD") || !strcmp(platform, "other"))
    {
        cmd = "xdg-open \"";
    }

    char *script = create_cmd(cmd, url);

    strcat(script, "\"");

    if (system(script) == -1)
    {
        printf("fatal: unable to open url\n");
    }

    free(script);
    return 0;
}
