/**
 * @file penguinspam.c
 * @author Lemuria
 * @brief Implementation file for penguin spam.
 * @date 2022-02-04
 *
 * @copyright MIT License
 *
 */

#include "penguinspam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int _is_valid_penguin(char *penguin_type)
{
    const char valid_penguins[][16] = {
        "emperor",
        "snares",
        "little",
        "yelloweyed",
        "gentoo",
        "african",
        "mixed"
    };

    for (int i = 0; i < LEN(valid_penguins); i++)
    {
        if (!strcasecmp(penguin_type, valid_penguins[i]))
        {
            return 1;
        }
        else
        {
            continue;
        }
    }

    return 0;
}

void free_psj_mem(penguin_spam_job *job) { free(job->__error__); }

int mk_penguin_spam_job(penguin_spam_job *job, int penguins, char *location,
                        char* penguin_type)
{
    job->__error__ = malloc(512);

    if (!strcmp(location, ""))
    {
        sprintf(job->__error__, "Error: Location cannot be an empty string");
        return PENGUIN_SPAM_ERROR;
    }
    if (penguins > MAX_PENGUINS)
    {
        sprintf(job->__error__,
                "Error: Too many penguins (limit is %d, "
                "tried to send %d)",
                MAX_PENGUINS, penguins);
        return PENGUIN_SPAM_TOO_MANY_PENGUINS;
    }
    if (penguins <= 0)
    {
        sprintf(job->__error__,
                "Error: penguins must be a positive number (tried to send %d)",
                penguins);
        return PENGUIN_SPAM_ERROR;
    }
    if (!_is_valid_penguin(penguin_type))
    {
        sprintf(job->__error__,
                 "Error: penguin type %s is invalid. Must be of: african, gentoo, yelloweyed, little, snares, emperor",
                 penguin_type);
        return PENGUIN_SPAM_INVALID_PENGUIN;
    }

    job->location = location;
    job->penguins = penguins;

    return PENGUIN_SPAM_OK;
}

int execute_penguin_spam_job(penguin_spam_job *job)
{
    printf("Acquired penguins.\n");
    printf("Sending %d penguins to %s, done.\n", job->penguins, job->location);
    printf("Successfully spammed penguins.\n");

    return PENGUIN_SPAM_OK;
}

int finish_penguin_spam_job(penguin_spam_job *job)
{
    free(job->__error__);
    return PENGUIN_SPAM_OK;
}
