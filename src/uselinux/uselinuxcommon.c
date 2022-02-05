#include "uselinuxcommon.h"

/**
 * @brief Activate Hackerman mode. Requires Kali Linux, a distribution that
 * comes preinstalled with several tools for hacking.
 *
 * @param distro Distribution being used. Must be Kali Linux.
 */
void hackerman(char *distro)
{
    if (!strcasecmp(distro, "kali"))
    {
        printf("Activating Hackerman mode....\n");
    }
    else
    {
        printf("fatal: --hackerman requires Kali Linux (use -d kali)\n");
        exit(1);
    }
}

/**
 * @brief Bash an operating system, insulting it.
 *
 * @param os The operating system to bash.
 *
 * @warning Supplying "Linux" or "GNU/Linux" will result in an abort.
 */
void bash_os(char *os)
{
    if (!strcasecmp(os, "Windows"))
    {
        printf("Windows, too much bloat!\n");
    }
    else if (!strcasecmp(os, "macOS"))
    {
        printf("macOS is proprietary garbage!\n");
    }
    else if (!strcasecmp(os, "GNU/Linux") || !strcasecmp(os, "Linux"))
    {
        printf("Ye shall not insult %s.", LINUXREF);
        abort();
    }
}

/**
 * @brief Snap at Snapcraft by criticizing the Snap packaging system.
 *
 * @param distro Distribution being used.
 */
void snap_at_snaps(char *distro)
{
    if (distro == NULL)
    {
        printf("Please supply \"ubuntu\" or \"mint\" as an argument to -d to "
               "snap at snaps.\n");
        printf("But snaps suck anyway....\n");
        return;
    }
    else
    {
        if (!strcasecmp(distro, "Ubuntu"))
        {
            printf("Ubuntu snaps are completely unacceptable!\n");
            printf("Reject snaps.\n");
            printf("Embrace APT.\n");
        }
        else if (!strcasecmp(distro, "Mint") ||
                 !strcasecmp(distro, "linuxmint"))
        {
            printf("Well, Linux Mint doesn't have snaps, yes?\n");
        }
        else
        {
            printf("No more snaps!\n");
        }
    }
}
