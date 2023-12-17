#ifndef VALIDATE_ARGS_H
#define VALIDATE_ARGS_H

#include "ancientpkg.h"

/**
 * @brief Check for missing args
 *
 * Check the archaeologists, passes, location, and expected_packages variables
 * and ensure that they are valid.
 *
 *
 * @param location Location argument
 * @param archaeologists Archaeologists argument
 * @param passes Passes argument
 * @param expected_packages Expected packages argument
 * @return int
 */
int validate_arguments(DigControlFlags *dcf, char *location,
                       int archaeologists, int passes, int expected_packages);

#endif /* VALIDATE_ARGS_H */
