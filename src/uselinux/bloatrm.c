#include "bloatrm.h"

/**
 * @brief Remove a single bloatware package.
 *
 * @param bloatware Name of bloatware to remove.
 */
void remove_bloatware_package(char *bloatware)
{
    printf("Removing bloatware %s.....", bloatware);

    for (int i = 0; i < 49 - strlen(bloatware); i++)
    {
        printf(" ");
    }

    fflush(stdout);
    int sleep = randint(10, 2300);
    msleep(sleep);
    printf("removed in %d ms\n", sleep);
}

/**
 * @brief Removes bloatware, such as Candy Crush (preinstalled on Windows).
 *
 * Inclusion of software in the bloatware list of this function should not be
 * taken seriously.
 */
void remove_bloatware()
{
    printf("Removing bloatware....\n");

    // Apps that are often criticized for being "bloatware",
    // or are called bloatware by some people.
    char bloatware[][64] = {"Candy Crush",     "Nero Burning ROM",
                            "Microsoft Word",  "Microsoft Office",
                            "Microsoft Excel", "Microsoft PowerPoint"};

    int i = 0;
    for (i = 0; i < LEN(bloatware); i++)
    {
        remove_bloatware_package(bloatware[i]);
    }
}
