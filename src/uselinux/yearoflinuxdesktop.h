#ifndef YEAROFLINUXDESKTOP_H
#define YEAROFLINUXDESKTOP_H

#include "uselinuxcommon.h"
#include <common/mtwister.h>
#include <common/utils.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Trigger a segfault if the user can't even
 * make a good guess about the year of the Linux desktop.
 */
void year_of_linux_desktop_segfault();

/**
 * @brief The year of the Linux desktop will arrive.... eventually.
 *
 * @param currentyr The current year.
 * @param linux_desktop_yr Year to predict as being the year of the Linux
 *                         desktop.
 */
void year_of_linux_desktop(int currentyr, int linux_desktop_yr);

/**
 * @brief Get the year of the Linux desktop. For real, this time.
 *
 * @return int The year of the Linux desktop.
 */
int get_year_of_linux_desktop();
#endif /* YEAROFLINUXDESKTOP_H */
