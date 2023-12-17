#ifndef ANCIENTPKG_UTILS_H
#define ANCIENTPKG_UTILS_H

/**
 * @brief Sleeping is disabled when --dry-run is specified. This wrapper
 * function checks the dry_run variable and sleeps if it is off, otherwise
 * this is a no-op.
 *
 * @param tms Sleep time in milliseconds
 */
void ancientpkg_msleep(int tms);

/**
 * @brief Set the dry run status for ancientpkg_msleep
 *
 * @param i
 */
void ancientpkg_set_dry_run(int i);

#endif /* ANCIENTPKG_UTILS_H */
