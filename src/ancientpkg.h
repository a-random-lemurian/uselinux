
#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H

/**
 * @brief Dig up ancient Debian packages.
 *
 */
void ancient_debian_packages();

/**
 * @brief Look for ancient Debian packages at a digsite.
 *
 * @param i Digsite number.
 *
 * @return int, Amount of Debian packages found.
 */
int check_digsite(int i);

#endif
