#ifndef USELINUXCOMMON_H
#define USELINUXCOMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef FSF_TERMINOLOGY
#define LINUXREF "GNU/Linux"
#elif INTERJECTION
#define LINUXREF "GNU plus Linux"
#else
#define LINUXREF "Linux"
#endif
#define LINUX_KERNEL_FIRST_RELEASE 1991
#define ANALYTICAL_ENGINE_YEAR 1833

/**
 * @brief Activate Hackerman mode. Requires Kali Linux, a distribution that
 * comes preinstalled with several tools for hacking.
 *
 * @param distro Distribution being used. Must be Kali Linux.
 */
void hackerman(char *distro);

/**
 * @brief Bash an operating system, insulting it.
 *
 * @param os The operating system to bash.
 *
 * @warning Supplying "Linux" or "GNU/Linux" will result in an abort.
 */
void bash_os(char *os);

/**
 * @brief Snap at Snapcraft by criticizing the Snap packaging system.
 *
 * @param distro Distribution being used.
 */
void snap_at_snaps(char *distro);

#endif /* USELINUXCOMMON_H */
