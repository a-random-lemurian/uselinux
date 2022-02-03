
#ifndef ANCIENTPKG_H
#define ANCIENTPKG_H

/**
 * @brief Dig up ancient Debian packages. This function automatically
 * calls check_digsite() to check digsites for ancient Debian
 * packages.
 * 
 * This function excavates digsites around the world. In a future version
 * of uselinux, more precise control over the geographic distribution of
 * digsites chosen may be provided.
 */
void ancient_debian_packages();

/**
 * @brief Look for ancient Debian packages at a digsite.
 *
 * @param i Digsite's numerical identifier.
 *
 * @return int, Amount of Debian packages found at the digsite.
 */
int check_digsite(int i);

#endif
