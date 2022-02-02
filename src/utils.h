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
 * @brief Converts a char* to a number.
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
#endif
