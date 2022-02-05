#ifndef BLOATRM_H
#define BLOATRM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * @brief Remove a single bloatware package.
 *
 * @param bloatware Name of bloatware to remove.
 */
void remove_bloatware_package(char *bloatware);

/**
 * @brief Removes bloatware, such as Candy Crush (preinstalled on Windows).
 *
 * Inclusion of software in the bloatware list of this function should not be
 * taken seriously.
 */
void remove_bloatware();

#endif /* BLOATRM_H */
