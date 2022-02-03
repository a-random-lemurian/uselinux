#ifndef UTILS_H
#define UTILS_H
#include "mtwister.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

/**
 * @brief Delay execution with millisecond precision.
 *
 * @param tms Milliseconds to sleep for.
 */
void msleep(int tms);

/**
 * @brief Print text with a typewriter effect.
 *
 * @param txt Text to print with typewriter effect.
 * @param freq Delay between each character in milliseconds.
 *
 * @todo Allow randomization of delay between each character.
 */
void typewriter(const char *txt, int freq);

/**
 * @brief Generate a random integer.
 *
 * @param min Minimum number.
 * @param max Maximum number.
 */
int randint(int min, int max);

/**
 * @brief Converts a char* to a number. Serves as a wrapper function for
 * strtol().
 *
 * @param str String to convert.
 * @param numbase Base of number (10 is decimal, 16 is hexadecimal.)
 * @return int
 */
int chartoint(char *str, int numbase);

/**
 * @brief Trigger a segmentation fault. Should be used for comedic purposes
 * only.
 *
 */
void trigger_segfault();

/**
 * @brief Trigger a random number generator and either cause a segmentation
 * fault or abort, depending on the randomly generated number's value. The
 * "threshold" can be altered to make a segmentation fault or abort more
 * likely. A lower threshold will result in a higher chance of a segmentation
 * fault, while a higher one will result in a higher chance of an abort.
 * 
 * The threshold value must be between 0 and 500. 0 will always trigger a
 * segmentation fault and 500 will always trigger an abort.
 * 
 * @note If the threshold is NULL, the default threshold of 250 is used instead.
 *
 * @param threshold An integer between 0 and 500. (`>= 0, <= 500`)
 */
void segfault_or_abort(int threshold);
#endif /* UTILS_H */
